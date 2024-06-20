#include "Enemy.h"

#include <numbers>

#include "MathUtils.h"
#include "Model.h"

Enemy::Enemy() {
    model_ = new Model;

    velocity_ = Vector3(-kWalkSpeed, 0, 0);
}

void Enemy::Initialize() {
    model_ = Model::CreateFromOBJ("enemy");

    worldTransform_.Initialize();
    worldTransform_.translation_ = Vector3(10, 1, 0);
    worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.f;

    walkMotionTimer_ = 0.f;

}

void Enemy::Update() {
    walkMotionTimer_ += 1.f / 60.f;

    float param = std::sin(walkMotionTimer_ / kWalkMotionTime * std::numbers::pi_v<float> *2);
    float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.f) / 2.f;

    worldTransform_.rotation_.x = MathUtils::DEG2RAD(radian);

    worldTransform_.translation_ += velocity_;

    worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {
    model_->Draw(worldTransform_, viewProjection);
}

void Enemy::SetMap(Map* map) {
    map;
}
