#include "DeathParticle.h"

#include "Model.h"

void DeathParticle::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	viewProjection_ = viewProjection;
    for(auto& worldTransform : worldTransforms_){
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
}

void DeathParticle::Update() {
	for(auto& worldTransform : worldTransforms_){
		worldTransform.UpdateMatrix();
	}
}

void DeathParticle::Draw() const {
	for(auto& worldTransform : worldTransforms_){
		model_->Draw(worldTransform, *viewProjection_);
	}
}
