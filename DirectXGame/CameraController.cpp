#include "CameraController.h"

#include <algorithm>

#include "MathUtils.h"
#include "Player.h"
#include "WorldTransform.h"

CameraController::~CameraController() {
    delete viewProjection_;
}

void CameraController::Initialize() {
    viewProjection_ = new ViewProjection();
	viewProjection_->farZ = 1200;
	viewProjection_->Initialize();
}

void CameraController::Update() {
    const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
    destination = targetWorldTransform.translation_ + targetOffset_ + target_->GetVelocity() * kVelocityBias;

    viewProjection_->translation_ = MathUtils::Lerp(viewProjection_->translation_, destination, kInterpolationRate);

    viewProjection_->translation_.x = std::clamp(viewProjection_->translation_.x, movableArea_.left, movableArea_.right);
    viewProjection_->translation_.y = std::clamp(viewProjection_->translation_.y, movableArea_.bottom, movableArea_.top);


    viewProjection_->UpdateMatrix();
}

void CameraController::Reset() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
    viewProjection_->translation_ = targetWorldTransform.translation_ + targetOffset_;
}
