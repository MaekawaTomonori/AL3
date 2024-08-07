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

    worldTransform_.translation_ += velocity_;
    worldTransform_.UpdateMatrix();
    worldTransform_.TransferMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) const {
    model_->Draw(worldTransform_, viewProjection);
}

void Player::Move() {
    Input* input = Input::GetInstance();
	if(input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)){
        Vector3 acceleration = {};

        if(input->PushKey(DIK_RIGHT)){
			acceleration.x += kAcceleration;

            if(velocity_.x < 0.f){
	            velocity_.x *= (1.f - kAttenuation);
            }

            if(lrDirection_ != LRDirection::kRight){
				lrDirection_ = LRDirection::kRight;
                turnFirstRotationY_ = worldTransform_.rotation_.y;
                turnTimer_ = 0.f;
			}
		}else if(input->PushKey(DIK_LEFT)){
	        acceleration.x -= kAcceleration;

            if(0.f < velocity_.x){
	            velocity_.x *= (1.f - kAttenuation);
			}

            if (lrDirection_ != LRDirection::kLeft){
                lrDirection_ = LRDirection::kLeft;
                turnFirstRotationY_ = worldTransform_.rotation_.y;
                turnTimer_ = 0.f;
            }
		}

        velocity_.x += std::clamp(acceleration.x, -kSpeedLimit, kSpeedLimit);
	}
	else{
        velocity_.x *= (1.f - kAttenuation);
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
