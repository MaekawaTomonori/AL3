#pragma once
#include "WorldTransform.h"
#include "Model.h"

enum class LRDirection{
	RIGHT,
	LEFT
};

class Map;
class Player{
	struct CollisionMapInfo{
		bool Ceiling = false;
		bool Landing = false;
		bool Wall = false;
		bool Collide = false;
		Vector3 velocity;
	};

	enum Corner{
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};
public:
	~Player();
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection) const;


	void SetMap(Map* map);

	const WorldTransform& GetWorldTransform() const;
	const Vector3& GetVelocity() const;

private:
	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.3f;
	static inline const float kAttenuationLanding = 0.3f;
	static inline const float kLimitRunSpeed = 1.f;

	static inline const float TURN_TIME = 0.3f;

	static inline const float GRAVITY_ACCELERATION = 0.01f;
	static inline const float LIMIT_FALL_SPEED = 4.9f;
	static inline const float JUMP_ACCELERATION = 0.6f;

	static inline const float kBlankSpace = 0.01f;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

private:
	Map* map_ = nullptr;

	Model* model_ = nullptr;
	WorldTransform worldTransform_ {};
	Vector3 velocity_ = {};
	LRDirection lrDirection_ = LRDirection::RIGHT;

	float turnFirstRotationY_ = 0.f;
	float turnTimer_ = 0.f;

	bool onGround_ = true;

private:
	void Move();
	void ReflectCollide(const CollisionMapInfo& info);
	Vector3 CornerPosition(const Vector3& center, Corner corner);

	void MapCollisionDetection(CollisionMapInfo& info);

	//hantei
	bool isCollideAbove(CollisionMapInfo& info);
	bool isCollideUnder(CollisionMapInfo& info);

	//true ji no shori
	void onCollisionCeiling(const CollisionMapInfo& info);
	void onCollisionFloor(const CollisionMapInfo& info);
};
