#include "Player.h"

Player::~Player() {
    delete model_;
}

void Player::Initialize() {
    worldTransform_.Initialize();
    model_ = new Model;
    model_ = Model::CreateFromOBJ("player");
}

void Player::Update() {
    worldTransform_.translation_ = {0, 2, 0};
    worldTransform_.UpdateMatrix();
    worldTransform_.TransferMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) const {
    model_->Draw(worldTransform_, viewProjection);
}
