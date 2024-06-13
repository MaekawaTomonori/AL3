#include "CameraController.h"

#include <algorithm>

#include "MathUtils.h"
#include "Player.h"

void CameraController::Initialize() {
	viewProjection_.farZ = 1200;
	viewProjection_.translation_.z = -50;
	viewProjection_.Initialize();
}

void CameraController::Update() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	const Vector3 targetVelocity = target_->GetVelocity();
	cameraDestination_ = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;

	viewProjection_.translation_ = MathUtils::Lerp(viewProjection_.translation_, cameraDestination_, kInterpolationRate);

	viewProjection_.translation_.x = std::clamp(viewProjection_.translation_.x, movableArea_.left , movableArea_.right);
	viewProjection_.translation_.y = std::clamp(viewProjection_.translation_.y, movableArea_.top, movableArea_.bottom);

	viewProjection_.UpdateMatrix();
}

void CameraController::Reset() {
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}
