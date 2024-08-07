#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	void operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

	Vector3 operator+(const Vector3& vector3) const {
		return { x + vector3.x, y + vector3.y, z + vector3.z };
	}

	Vector3 operator-(const Vector3& vector3) const {
		return { x - vector3.x, y - vector3.y, z - vector3.z };
	}

	Vector3 operator*(const Vector3& vector3) const {
		return { x * vector3.x, y * vector3.y, z * vector3.z };
	}

	Vector3 operator*(const float& other) const {
		return { this->x * other, this->y * other, this->z * other };
	}
};