#pragma once
#include "ViewProjection.h"

class Player;
class CameraController{
public:
	struct Rect{
        float left = 0;
        float right = 1;
        float bottom = 0;
        float top = 1;
	};

    ~CameraController();
    void Initialize();
    void Update();
    void Reset();

    void SetTarget(Player* target) {
		target_ = target;
	}

    ViewProjection* GetViewProjection() const {
        return viewProjection_;
    }

    void SetMovableArea(Rect area) {
		movableArea_ = area;
	}
private:
	static inline const float kInterpolationRate = 0.6f;
    static inline const float kVelocityBias = 0.4f;
private:
	ViewProjection* viewProjection_ = nullptr;
    Player* target_ = nullptr;
    Vector3 targetOffset_ = { 0.f, 0.f, -15.f };
    Rect movableArea_ = {0, 100, 0, 100};

    Vector3 destination {};
};

