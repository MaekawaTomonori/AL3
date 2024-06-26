#include "Enemy.h"

#include <numbers>

#include "MathUtils.h"
#include "Model.h"

Enemy::Enemy() {
    velocity_ = Vector3(-kWalkSpeed, 0, 0);
}

void Enemy::Initialize(Model* model, Vector3 pos) {
    model_ = model;

    worldTransform_.Initialize();
    worldTransform_.translation_ = pos;
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

Vector3 Enemy::GetWorldPosition() const {
    return Vector3 {
        worldTransform_.matWorld_.m[3][0],
        worldTransform_.matWorld_.m[3][1],
        worldTransform_.matWorld_.m[3][2]
    };
}

AABB Enemy::GetAABB() const {
    Vector3 worldPos = GetWorldPosition();

    return AABB {
    {worldPos.x - kWidth / 2.f, worldPos.y - kHeight / 2.f, worldPos.z - kWidth / 2.f},
        {worldPos.x + kWidth / 2.f, worldPos.y + kHeight / 2.f, worldPos.z + kWidth / 2.f}
    };
}

void Enemy::OnCollision(Player* player) {
    (void)player;
}
