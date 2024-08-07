#pragma once
#include "WorldTransform.h"
#include "Model.h"

enum class LRDirection{
	kRight,
    kLeft
};

class Player{
public:
    ~Player();
    void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
    void Update();
    void Draw(const ViewProjection& viewProjection) const;
private: // methods
	void Move();
    void Turning();

private://static
    static inline const float kAcceleration = 0.05f;

    static inline const float kAttenuation = 0.2f;

    static inline const float kSpeedLimit = 0.2f;


    static inline const float kTimeTurn = 0.3f;

private:
    WorldTransform worldTransform_{};
    Model* model_ = nullptr;
    ViewProjection* viewProjection_ = nullptr;

    Vector3 velocity_{};
    LRDirection lrDirection_ = LRDirection::kRight;

    float turnFirstRotationY_ = 0.f;
    float turnTimer_ = 0.f;
};
