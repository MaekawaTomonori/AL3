#pragma once
#include "WorldTransform.h"
#include "Model.h"

enum class LRDirection{
	RIGHT,
	LEFT
};

class Map;
class Player{
public:
	~Player();
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection) const;
	void applyMap(const Map& map);
	private:
	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.3f;
	static inline const float kLimitRunSpeed = 1.f;

	static inline const float TURN_TIME = 0.3f;

	static inline const float GRAVITY_ACCELERATION = 9.8f / 60.f;
	static inline const float LIMIT_FALL_SPEED = 10;
	static inline const float JUMP_ACCELERATION = 5;

	private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_ {};
	Vector3 velocity_ = {};
	LRDirection lrDirection_ = LRDirection::RIGHT;

	float turnFirstRotationY_ = 0.f;
	float turnTimer_ = 0.f;

	bool onGround_ = true;

	private:
	void Move();
};
