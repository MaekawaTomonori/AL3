#include "MathUtils.h"
#include <cmath>
#include <cassert>
#include <numbers>

#include "Vector3.h"


Matrix4x4 MathUtils::MakeTranslateMatrix(const Vector3& velocity) {
    return Matrix4x4 {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        velocity.x, velocity.y, velocity.z, 1
    };
}

Matrix4x4 MathUtils::MakeScaleMatrix(const Vector3& scale) {
    return Matrix4x4 {
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    };
}

Vector3 MathUtils::Transform(const Vector3& vector, const Matrix4x4& matrix) {
    Vector3 v = {
        vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1 * matrix.m[3][0],
        vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1 * matrix.m[3][1],
        vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1 * matrix.m[3][2]
    };
    const float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1 * matrix.m[3][3];
    assert(w != 0);
    if (w != 1){
        v.x /= w;
        v.y /= w;
        v.z /= w;
    }
    return v;
}

Matrix4x4 MathUtils::MakeRotateX(const float rad) {
    return {
        1, 0, 0, 0,
        0, std::cosf(rad), std::sinf(rad), 0,
        0, -std::sinf(rad), std::cosf(rad), 0,
        0, 0, 0, 1
    };
}

Matrix4x4 MathUtils::MakeRotateY(float rad) {
    return Matrix4x4 {
        std::cosf(rad), 0, -std::sinf(rad), 0,
        0, 1, 0, 0,
        std::sinf(rad), 0, std::cosf(rad), 0,
        0, 0, 0, 1
    };
}

Matrix4x4 MathUtils::MakeRotateZ(const float rad) {
    return Matrix4x4 {
        std::cosf(rad), std::sinf(rad), 0, 0,
        -std::sinf(rad), std::cosf(rad), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

Matrix4x4 MathUtils::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
    return MakeScaleMatrix(scale) * (MakeRotateX(rotate.x) * MakeRotateY(rotate.y) * MakeRotateZ(rotate.z)) * MakeTranslateMatrix(translate);
}

Vector3 MathUtils::Lerp(const Vector3& value, const Vector3& destination, float percent) {
    return value + (destination - value) * percent;
}

float MathUtils::DEG2RAD(float deg) {
    return deg /360.f * 2 * std::numbers::pi_v<float>;
}
