#include "Player.h"

Player::~Player() {
    delete model_;
}

void Player::Initialize() {
    worldTransform_.Initialize();
    worldTransform_.translation_ = {0, 2, 0};
    model_ = new Model;
    model_ = Model::CreateFromOBJ("player");
}

void Player::Update() {
    worldTransform_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) const {
    model_->Draw(worldTransform_, viewProjection);
}
