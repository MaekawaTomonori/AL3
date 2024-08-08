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
	static inline const float kWalkSpeed = 0.04f;
	static inline const float kWalkMotionAngleStart = 0.f;
	static inline const float kWalkMotionAngleEnd = 45.f;
	static inline const float kWalkMotionTime = 1.f;

	WorldTransform worldTransform_ {};
    Model* model_ = nullptr;
    ViewProjection* viewProjection_ = nullptr;
    Vector3 velocity_ = {};

    float walkTimer_ = 0.f;
};

