#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Player{
public:
~Player();
void Initialize();
void Update();
void Draw(const ViewProjection& viewProjection) const;
private:
Model* model_ = nullptr;
WorldTransform worldTransform_{};
};
