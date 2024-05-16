#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Skydome{
public:
	~Skydome();
	void Initialize();
	void Update();
	void Draw(const ViewProjection& viewProjection) const;

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};

