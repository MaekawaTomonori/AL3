#pragma once
#include "AABB.h"
#include "WorldTransform.h"


class Player;
class Model;
class Map;
class ViewProjection;

class Enemy{
public:
	Enemy();

	void Initialize(Model* model, Vector3 pos = Vector3());
	void Update();
	void Draw(const ViewProjection& viewProjection);

	void SetMap(Map* map);

	Vector3 GetWorldPosition() const;
	AABB GetAABB() const;

	void OnCollision(Player* player);

private: //
	static inline const float kWalkSpeed = 0.03f;

	static inline const float kWalkMotionAngleStart = 0.f;
	static inline const float kWalkMotionAngleEnd = 45.f;

	static inline const float kWalkMotionTime = 0.5f;

	static inline const float kWidth = 1.f;
	static inline const float kHeight = 1.f;

private: // 
	WorldTransform worldTransform_;
	Model* model_;

	Vector3 velocity_;

	float walkMotionTimer_ = 0.f;
};

