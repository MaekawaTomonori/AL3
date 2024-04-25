#pragma once
#include <cstdint>
#include "Model.h"
#include "WorldTransform.h"

class Player{
public:
~Player();
void Initialize(Model* model, uint32_t texture, ViewProjection* viewProjection);
void Update();
void Draw() const;
private:
uint32_t textureHandle_ = 0u;
Model* model_ = nullptr;
WorldTransform worldTransform_;
ViewProjection* viewProjection_;
};
