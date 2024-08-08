#include "Enemy.h"

#include <numbers>

#include "MathUtils.h"
#include "Model.h"

Enemy::~Enemy() {
}

void Enemy::Initialize(Model* model, ViewProjection* viewProjection) {
    model_ = model;
	viewProjection_ = viewProjection;
    worldTransform_.Initialize();
    worldTransform_.translation_ = {6, 1, 0};
    worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.f;
    velocity_ = {-kWalkSpeed, 0,0};
    walkTimer_ = 0.f;
}

void Enemy::Update() {
    walkTimer_ += 1.f / 60.f;
    float param = std::sin(2 * std::numbers::pi_v<float> *(walkTimer_ / kWalkMotionTime));
    float deg = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.f) / 2.f;

    worldTransform_.rotation_.x = MathUtils::DEG2RAD(deg);

    worldTransform_.translation_ += velocity_;

    worldTransform_.UpdateMatrix();
}

void Enemy::Draw() const {
    model_->Draw(worldTransform_, *viewProjection_);
}
