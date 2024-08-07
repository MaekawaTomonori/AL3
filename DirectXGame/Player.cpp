#define NOMINMAX
#include "Player.h"

#include <algorithm>
#include <numbers>

#include "Input.h"

Player::~Player() {
}

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
    worldTransform_.Initialize();
    worldTransform_.translation_ = position;
    worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.f;
    model_ = model;
    viewProjection_ = viewProjection;

    velocity_ = {0,0,0};
}

void Player::Update() {
    Move();
    Turning();

    //接地判定
    bool landing = false;

    if (velocity_.y < 0){
        if (worldTransform_.translation_.y <= 1.f){
            landing = true;
        }
    }

    if (onGround_){
        if (velocity_.y > 0.f){
            onGround_ = false;
        }
    } else{
        if (landing){
            worldTransform_.translation_.y = 1.f;
            velocity_.x *= (1.f - kAttenuation);
            velocity_.y = 0;
            onGround_ = true;
        }
    }

    worldTransform_.translation_ += velocity_;
    worldTransform_.UpdateMatrix();
    worldTransform_.TransferMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) const {
    model_->Draw(worldTransform_, viewProjection);
}

WorldTransform& Player::GetWorldTransform() {
    return worldTransform_;
}

void Player::Move() {
    Input* input = Input::GetInstance();

    if (onGround_){
        if (input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)){
            Vector3 acceleration = {};

            if (input->PushKey(DIK_RIGHT)){
                acceleration.x += kAcceleration;

                if (velocity_.x < 0.f){
                    velocity_.x *= (1.f - kAttenuation);
                }

                if (lrDirection_ != LRDirection::kRight){
                    lrDirection_ = LRDirection::kRight;
                    turnFirstRotationY_ = worldTransform_.rotation_.y;
                    turnTimer_ = 0.f;
                }
            } else if (input->PushKey(DIK_LEFT)){
                acceleration.x -= kAcceleration;

                if (0.f < velocity_.x){
                    velocity_.x *= (1.f - kAttenuation);
                }

                if (lrDirection_ != LRDirection::kLeft){
                    lrDirection_ = LRDirection::kLeft;
                    turnFirstRotationY_ = worldTransform_.rotation_.y;
                    turnTimer_ = 0.f;
                }
            }

            velocity_.x += std::clamp(acceleration.x, -kSpeedLimit, kSpeedLimit);
        } else{
            velocity_.x *= (1.f - kAttenuation);
        }


        if(input->PushKey(DIK_UP)){
	        velocity_ += {0, kJumpAcceleration, 0};
        }
    } else{
        velocity_ += {0, -kGravityAcceleration, 0};
        velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
    }
}

void Player::Turning() {
    if(turnTimer_ < kTimeTurn){
		turnTimer_ += 1.f / 60.f;
    	float destinationRotationYTable[] = {
            std::numbers::pi_v<float> / 2.f,
            std::numbers::pi_v<float> *3.f / 2.f
        };
    	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		worldTransform_.rotation_.y = destinationRotationY;
	}   
}
