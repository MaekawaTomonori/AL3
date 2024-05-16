#include "Skydome.h"

#include "ViewProjection.h"

Skydome::~Skydome() {
    delete model_;
}

void Skydome::Initialize() {
    worldTransform_.Initialize();
    model_ = new Model();
    model_ = Model::CreateFromOBJ("skydome", true);
}

void Skydome::Update() {
	
}

void Skydome::Draw(const ViewProjection& viewProjection) const {
    model_->Draw(worldTransform_, viewProjection);
}
