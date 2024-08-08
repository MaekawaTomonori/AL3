#include "DeathParticle.h"

#include "MathUtils.h"
#include "Model.h"

void DeathParticle::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	viewProjection_ = viewProjection;

	isFinished_ = false;
	counter_ = 0.f;

    for(auto& worldTransform : worldTransforms_){
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticle::Update() {
	if (isFinished_)return;
	counter_ += 1.f / 60.f;
	for(uint32_t i = kNumParticles; i --> 0;){
		Vector3 velocity = {kSpeed, 0,0};
		float angle = kAngleUnit * i;
		Matrix4x4 matrixRotation = MathUtils::MakeRotateZ(angle);
		velocity = MathUtils::Transform(velocity, matrixRotation);


		if(kDuration <= counter_){
			counter_ = kDuration;

			isFinished_ = true;
		}


		worldTransforms_[i].translation_ += velocity;
		worldTransforms_[i].UpdateMatrix();
	}
}

void DeathParticle::Draw() const {
	if(isFinished_)return;
	for(auto& worldTransform : worldTransforms_){
		model_->Draw(worldTransform, *viewProjection_);
	}
}
