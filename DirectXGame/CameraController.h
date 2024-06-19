#pragma once
#include "ViewProjection.h"



class Player;

class CameraController{
public:
	struct Rect{
		float left = 0.f;
		float right = 1.f;
		float bottom = 0.f;
		float top = 1.f;
	};

	void Initialize();
	void Update();

	void Reset();

	const ViewProjection& GetViewProjection() const {
		return viewProjection_;
	}

	void SetTarget(Player* target) {
		target_ = target;
	}
	void SetMovableArea(const Rect& area) {
		movableArea_ = area;
	}
private:
	static inline const float kInterpolationRate = 0.4f;
	static inline const float kVelocityBias = 1.2f;
	static inline const Rect kRange {-1, 1, -1, 1};

	ViewProjection viewProjection_ = {};

	//追従するターゲット
	Player* target_ = nullptr;

	Vector3 targetOffset_ = {0,0,-20.f};

	Vector3 cameraDestination_{};

	Rect movableArea_ = {0, 100, 0, 100};
};

