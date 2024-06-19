#define NOMINMAX

#include "Player.h"

#include <numbers>
#include <algorithm>
#include <DebugText.h>

#include "Ease.h"
#include "Input.h"
#include "MapChipField.h"


Player::~Player() {
    delete model_;
}

void Player::Initialize() {
	model_ = new Model;
    model_ = Model::CreateFromOBJ("player");
    worldTransform_.Initialize();
    worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.f;
}

void Player::Update() {
    //movement
    Move();

    CollisionMapInfo info;
    info.velocity = velocity_;

    MapCollisionDetection(info);
    ReflectCollide(info);

    worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) const {
    model_->Draw(worldTransform_, viewProjection);
}

void Player::MapCollisionDetection(CollisionMapInfo& info) {
    isCollideAbove(info);
    onCollisionCeiling(info);
}

void Player::SetMap(Map* map) {
	if(const nullable<Vector3> pos = map->getPlayer()){
        worldTransform_.translation_ = Vector3(pos);
    }
    map_ = map;
}

const WorldTransform& Player::GetWorldTransform() const {
	return worldTransform_;
}

const Vector3& Player::GetVelocity() const {
	return velocity_;
}

void Player::Move() {
    if(0 < turnTimer_){
        turnTimer_ += 1.f / 60.f;


        float destinationRotationYTable[] = {
            std::numbers::pi_v<float> / 2.f,
            std::numbers::pi_v<float> *3.f / 2.f
        };

        //未完成・不完全
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
        worldTransform_.rotation_.y = Ease::In::Cubic(turnTimer_/ TURN_TIME) * destinationRotationY;
    }

	bool landing = false;
    if(velocity_.y < 0){
	    if(worldTransform_.translation_.y <= 2.f){
            landing = true;
	    }
    }
    //jump
    if(onGround_){
        if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_D)){
            Vector3 acceleration = {};

            if (Input::GetInstance()->PushKey(DIK_A)){
                if(velocity_.x < 0){
                    velocity_.x *= (1.f - kAttenuation);
                }

	            acceleration.x -= kAcceleration;

	            if (lrDirection_ != LRDirection::RIGHT){
                    lrDirection_ = LRDirection::RIGHT;
	                turnFirstRotationY_ = worldTransform_.rotation_.y;
	                turnTimer_ = 0.f;
	            }
            }
            else if(Input::GetInstance()->PushKey(DIK_D)){
                if (0 < velocity_.x){
                    velocity_.x *= (1.f - kAttenuation);
                }

                acceleration.x += kAcceleration;

                if (lrDirection_ != LRDirection::LEFT){
                    lrDirection_ = LRDirection::LEFT;
                    turnFirstRotationY_ = worldTransform_.rotation_.y;
                    turnTimer_ = 0.f;
                }
            }

            velocity_ += acceleration;

            velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
        } else{
            velocity_.x *= (1.f - kAttenuation);
        }

	    if(Input::GetInstance()->PushKey(DIK_SPACE)){
            velocity_ += Vector3(0, JUMP_ACCELERATION, 0);
            onGround_ = false;
	    }
    }else{
        velocity_ += Vector3(0, -GRAVITY_ACCELERATION, 0);
        velocity_.y = std::max(velocity_.y, -LIMIT_FALL_SPEED);

        if (landing){
            worldTransform_.translation_.y = 2.f;
            velocity_.x *= (1.f - kAttenuation);
            velocity_.y = 0;
            onGround_ = true;
        }
    }
}

void Player::ReflectCollide(const CollisionMapInfo& info) {
    worldTransform_.translation_ += info.velocity;
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {
    Vector3 offsetTable[kNumCorner] = {
        Vector3{ -kWidth / 2.f, -kHeight / 2.f, 0},
        Vector3{ +kWidth / 2.f, -kHeight / 2.f, 0},
        Vector3{ +kWidth / 2.f, +kHeight / 2.f, 0},
        Vector3{ -kWidth / 2.f, +kHeight / 2.f, 0},
    };

    return center + offsetTable[static_cast<uint32_t>(corner)];
}

bool Player::isCollideAbove(CollisionMapInfo& info) {
    if (info.velocity.y <= 0)return false;

    std::array<Vector3, 4> positionNew;
    for (uint32_t i = 0; i < positionNew.size(); ++i){
        positionNew[i] = CornerPosition(worldTransform_.translation_ + info.velocity, static_cast<Corner>(i));
    }

    bool hit = false;

    Map::IndexSet indexSet;
    {
	    indexSet = map_->GetMapIndexSetByPosition(positionNew[kLeftTop]);
 	    MapBlockType blockType = map_->GetMapBlockTypeByIndex(indexSet);

    	if(blockType == MapBlockType::BLOCK){
    		hit = true;
    	}
	}
	{
	    indexSet = map_->GetMapIndexSetByPosition(positionNew[kRightTop]);
	    MapBlockType blockType = map_->GetMapBlockTypeByIndex(indexSet);

    	if(blockType == MapBlockType::BLOCK){
    		hit = true;
    	}
	}

    if(hit){
        indexSet = map_->GetMapIndexSetByPosition(positionNew[kLeftTop]);
        Map::Rect rect = map_->GetRectByIndex(indexSet);
        info.velocity.y = std::max(0.f, info.velocity.y - (rect.Bottom - positionNew[kLeftTop].y));
        info.Ceiling = true;
    }

    return hit;
}

void Player::onCollisionCeiling(const CollisionMapInfo& info) {
    if(info.Ceiling){
        DebugText::GetInstance()->ConsolePrintf("Hit Ceiling\n");
        velocity_.y = 0;
    }
}
