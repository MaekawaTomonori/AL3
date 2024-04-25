#include "Player.h"

#include <assert.h>

#include "TextureManager.h"

Player::~Player() {
}

void Player::Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection) {
    assert(model);
    assert(viewProjection);

    model_ = model;
    textureHandle_ = texture;
    viewProjection_ = viewProjection;
    worldTransform_.Initialize();
}

void Player::Update() {
    worldTransform_.TransferMatrix();
}

void Player::Draw() const {
    model_->Draw(
        worldTransform_,
        *viewProjection_,
        textureHandle_
    );
}
