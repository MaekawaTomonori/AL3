#pragma once
#include "AABB.h"
#include "WorldTransform.h"

class Player;
class ViewProjection;
class Model;

class Enemy{
public:
    ~Enemy();
    void Initialize(Model* model, ViewProjection* viewProjection, Vector3 position);
    void Update();
    void Draw() const;

    Vector3 GetWorldPosition() const;
    AABB GetAABB() const;

    void onCollision(Player* player);

private:
	static inline const float kWalkSpeed = 0.04f;
	static inline const float kWalkMotionAngleStart = 0.f;
	static inline const float kWalkMotionAngleEnd = 45.f;
	static inline const float kWalkMotionTime = 1.f;
	static inline const float kWidth = 1.f;
	static inline const float kHeight = 1.f;

	WorldTransform worldTransform_ {};
    Model* model_ = nullptr;
    ViewProjection* viewProjection_ = nullptr;
    Vector3 velocity_ = {};

    float walkTimer_ = 0.f;
};

