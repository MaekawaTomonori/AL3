#include "Enemy.h"

#include <numbers>

#include "MathUtils.h"
#include "Model.h"

Enemy::~Enemy() {
}

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, Vector3 position) {
    model_ = model;
	viewProjection_ = viewProjection;
    worldTransform_.Initialize();
    worldTransform_.translation_ = position;
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

Vector3 Enemy::GetWorldPosition() const {
    return {
		worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2],
	};
}

AABB Enemy::GetAABB() const {
    Vector3 center = GetWorldPosition();
    return {
		center.x - kWidth / 2, center.y - kHeight / 2, center.z - kWidth / 2,
		center.x + kWidth / 2, center.y + kHeight / 2, center.z + kWidth / 2
	};
}

void Enemy::onCollision(Player* player) {
    (void)player;
}
