#pragma once
#include <array>
#include <cstdint>
#include <numbers>

#include "ObjectColor.h"
#include "WorldTransform.h"

class ViewProjection;
class Model;

class DeathParticle{
public:
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	void Update();
	void Draw() const;

private:
	static inline const uint32_t kNumParticles = 8;
	static inline const float kDuration = 1.f;
	static inline const float kSpeed = 0.05f;
	static inline const float kAngleUnit = 2.f * std::numbers::pi_v<float> / kNumParticles;

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	std::array<WorldTransform, kNumParticles> worldTransforms_;

	bool isFinished_ = false;
	float counter_ = 0.f;

	ObjectColor objectColor_;
	Vector4 color_ {};
};
