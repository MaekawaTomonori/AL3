#pragma once
#include <array>
#include <cstdint>

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

	Model* model_ = nullptr;
	ViewProjection* viewProjection_ = nullptr;

	std::array<WorldTransform, kNumParticles> worldTransforms_;
};
