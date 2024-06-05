#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	void operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
	}
};