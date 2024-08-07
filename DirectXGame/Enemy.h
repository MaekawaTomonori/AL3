#pragma once
#include "WorldTransform.h"

class ViewProjection;
class Model;

class Enemy{
public:
    ~Enemy();
    void Initialize(Model* model, ViewProjection* viewProjection);
    void Update();
    void Draw() const;

private:
	WorldTransform worldTransform_ {};
    Model* model_ = nullptr;
    ViewProjection* viewProjection_ = nullptr;
};

