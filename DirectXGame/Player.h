#pragma once
#include "WorldTransform.h"
#include "Model.h"

class MapChipField;

enum class LRDirection{
	kRight,
    kLeft
};

struct CollisionMapInfo;
class Player{
	struct CollisionMapInfo{
        bool ceiling = false; 
        bool landing = false;
        bool wall = false;
        Vector3 move;
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
    void Initialize(Model* model, ViewProjection* viewProjection);
    void Update();
    void Draw(const ViewProjection& viewProjection) const;
    WorldTransform& GetWorldTransform();
    const Vector3& GetVelocity() const {
		return velocity_;
	}
    void SetMapChipField(MapChipField* mapChipField);

private: // methods
	void Move();
    void Turning();

    Vector3 CornerPosition(const Vector3& center, Corner corner);

    void CheckMapCollision(CollisionMapInfo& info);

    void isCeiling(CollisionMapInfo& info);
    void isLanding(CollisionMapInfo& info);

    void ReflectCollisionResult(const CollisionMapInfo& info);

    void onCollision(const CollisionMapInfo& info);

    void onHitCeiling(const CollisionMapInfo& info);

    void onLanding(CollisionMapInfo& info);

private://static
    static inline const float kAcceleration = 0.05f;

    static inline const float kAttenuation = 0.2f;

    static inline const float kSpeedLimit = 0.2f;


    static inline const float kTimeTurn = 0.3f;


    static inline const float kJumpAcceleration = 0.2f;

    static inline const float kGravityAcceleration = 0.01f;

	static inline const float kLimitFallSpeed = 0.8f;

    static inline const float kWidth = 0.8f;

    static inline const float kHeight = 0.8f;

    static inline const float kBlank = 0.1f;

private:
    

    WorldTransform worldTransform_{};
    Model* model_ = nullptr;
    ViewProjection* viewProjection_ = nullptr;
    MapChipField* mapChipField_ = nullptr;

    Vector3 velocity_{};
    LRDirection lrDirection_ = LRDirection::kRight;

    float turnFirstRotationY_ = 0.f;
    float turnTimer_ = 0.f;

    bool onGround_ = true;
};
