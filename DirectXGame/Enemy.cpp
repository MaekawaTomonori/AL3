#include "Enemy.h"
#include "Model.h"

Enemy::~Enemy() {
}

void Enemy::Initialize(Model* model, ViewProjection* viewProjection) {
    model_ = model;
	viewProjection_ = viewProjection;
    worldTransform_.Initialize();
    worldTransform_.translation_ = {6, 1, 0};
}

void Enemy::Update() {

    worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void Enemy::Draw() const {
    model_->Draw(worldTransform_, *viewProjection_);
}
