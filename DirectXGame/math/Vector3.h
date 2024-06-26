#pragma once
#include <cstdlib>

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	Vector3 operator+(const Vector3& other) const {
		return Vector3 {
			x + other.x,
			y + other.y,
			z + other.z
		};
	}

	void operator+=(const Vector3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
	}

	Vector3 operator-(const Vector3& other) const {
		return Vector3 {
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	Vector3 operator*(const float& other) const {
		return Vector3 {
			x * other,
			y * other,
			z * other
		};
	}

	static Vector3 Random() {
		return Vector3 {
			static_cast<float>(rand() % 100) / 100.f,
			static_cast<float>(rand() % 100) / 100.f,
			static_cast<float>(rand() % 100) / 100.f
		};
	}
};