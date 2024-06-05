#define NOMINMAX

#include "Player.h"

#include <numbers>
#include <algorithm>

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
    //KeyInput
    Move();

    //movement
    worldTransform_.translation_ += velocity_;

    //matrix calculation
    worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) const {
    model_->Draw(worldTransform_, viewProjection);
}

void Player::applyMap(const Map& map) {
	if(const nullable<Vector3> pos = map.getPlayer()){
        worldTransform_.translation_ = Vector3(pos);
    }
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
	    if(worldTransform_.translation_.y <= 1.0f){
            landing = true;
	    }
    }
    //jump
    if(onGround_){
        if (Input::GetInstance()->PushKey(DIK_A) || Input::GetInstance()->PushKey(DIK_D)){
            Vector3 acceleration = {};
            acceleration.x = static_cast<float>(Input::GetInstance()->PushKey(DIK_D) - Input::GetInstance()->PushKey(DIK_A)) * kAcceleration;

            if (lrDirection_ != (lrDirection_ = acceleration.x < 0 ? LRDirection::LEFT : LRDirection::RIGHT)){
                turnFirstRotationY_ = worldTransform_.rotation_.y;
                turnTimer_ = 0.f;
            }


            //brake
            if (0 < velocity_.x && acceleration.x < 0 || velocity_.x < 0 && 0 < acceleration.x){
                velocity_.x *= (1.f - kAttenuation);
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
            worldTransform_.translation_.y = 1.f;
            velocity_.x *= (1.f - kAttenuation);
            velocity_.y = 0;
            onGround_ = true;
        }
    }
}
