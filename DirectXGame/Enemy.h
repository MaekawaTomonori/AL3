#pragma once
#include "WorldTransform.h"


class Model;
class Map;
class ViewProjection;

class Enemy{
public:
Enemy();

void Initialize();
void Update();
void Draw(const ViewProjection& viewProjection);

void SetMap(Map* map);

private:
static inline const float kWalkSpeed = 0.03f;

static inline const float kWalkMotionAngleStart = 0.f;
static inline const float kWalkMotionAngleEnd = 45.f;

static inline const float kWalkMotionTime = 0.5f;

WorldTransform worldTransform_;
Model* model_;

Vector3 velocity_;

float walkMotionTimer_ = 0.f;
};

