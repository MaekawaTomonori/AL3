#pragma once
#include "Matrix4x4.h"

struct Vector3;

namespace MathUtils{
    Matrix4x4 MakeTranslateMatrix(const Vector3& velocity);
    Matrix4x4 MakeScaleMatrix(const Vector3& scale);
    Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);

    Matrix4x4 MakeRotateX(float rad);
    Matrix4x4 MakeRotateY(float rad);
    Matrix4x4 MakeRotateZ(float rad);

    Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
};

