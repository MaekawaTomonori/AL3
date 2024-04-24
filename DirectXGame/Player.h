#pragma once
#include <cstdint>
#include "WorldTransform.h"
#include "Model.h"

class Player{
public:
void Initialize();
void Update();
void Draw();
private:
uint32_t textureHandle_ = 0u;
Model* model_ = nullptr;
WorldTransform worldTransform_;
};