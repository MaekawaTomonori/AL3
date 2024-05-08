#pragma once
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];

    Matrix4x4 operator+(const Matrix4x4& other) const {
        return Matrix4x4 {
            m[0][0] + other.m[0][0],
            m[0][1] + other.m[0][1],
            m[0][2] + other.m[0][2],
            m[0][3] + other.m[0][3],
            m[1][0] + other.m[1][0],
            m[1][1] + other.m[1][1],
            m[1][2] + other.m[1][2],
            m[1][3] + other.m[1][3],
            m[2][0] + other.m[2][0],
            m[2][1] + other.m[2][1],
            m[2][2] + other.m[2][2],
            m[2][3] + other.m[2][3],
            m[3][0] + other.m[3][0],
            m[3][1] + other.m[3][1],
            m[3][2] + other.m[3][2],
            m[3][3] + other.m[3][3]
        };
    }
    Matrix4x4 operator-(const Matrix4x4& other) const {
        return Matrix4x4 {
            m[0][0] - other.m[0][0],
            m[0][1] - other.m[0][1],
            m[0][2] - other.m[0][2],
            m[0][3] - other.m[0][3],
            m[1][0] - other.m[1][0],
            m[1][1] - other.m[1][1],
            m[1][2] - other.m[1][2],
            m[1][3] - other.m[1][3],
            m[2][0] - other.m[2][0],
            m[2][1] - other.m[2][1],
            m[2][2] - other.m[2][2],
            m[2][3] - other.m[2][3],
            m[3][0] - other.m[3][0],
            m[3][1] - other.m[3][1],
            m[3][2] - other.m[3][2],
            m[3][3] - other.m[3][3]
        };
    }
    Matrix4x4 operator*(const float& other) const {
        return Matrix4x4 {
            m[0][0] * other,
            m[0][1] * other,
            m[0][2] * other,
            m[0][3] * other,
            m[1][0] * other,
            m[1][1] * other,
            m[1][2] * other,
            m[1][3] * other,
            m[2][0] * other,
            m[2][1] * other,
            m[2][2] * other,
            m[2][3] * other,
            m[3][0] * other,
            m[3][1] * other,
            m[3][2] * other,
            m[3][3] * other
        };
    }
    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 matrix {};
        for (int i = 0; i < 4; ++i){
            for (int j = 0; j < 4; ++j){
                for (int k = 0; k < 4; ++k){
                    matrix.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return matrix;
    }
    Matrix4x4 operator/(const float& other) const {
        return Matrix4x4 {
            m[0][0] / other,
            m[0][1] / other,
            m[0][2] / other,
            m[0][3] / other,
            m[1][0] / other,
            m[1][1] / other,
            m[1][2] / other,
            m[1][3] / other,
            m[2][0] / other,
            m[2][1] / other,
            m[2][2] / other,
            m[2][3] / other,
            m[3][0] / other,
            m[3][1] / other,
            m[3][2] / other,
            m[3][3] / other
        };
    }
    Matrix4x4 Inverse() const {
        float a = m[0][0] * m[1][1] * m[2][2] * m[3][3] + m[0][0] * m[1][2] * m[2][3] * m[3][1] + m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] - m[0][1] * m[1][0] * m[2][2] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1] + m[0][2] * m[1][0] * m[2][1] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2] + m[0][1] * m[1][2] * m[2][0] * m[3][3] + m[0][2] * m[1][3] * m[2][0] * m[3][1] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][1] * m[1][3] * m[2][0] * m[3][2] - m[0][1] * m[1][2] * m[2][3] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] - m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][2] * m[2][1] * m[3][0] + m[0][2] * m[1][1] * m[2][3] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0];
        return Matrix4x4 {
            (m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][3] * m[2][2] * m[3][1] - m[1][2] * m[2][1] * m[3][3] - m[1][2] * m[2][3] * m[3][2]),
            (-m[0][1] * m[2][2] * m[3][3] - m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2] + m[0][3] * m[2][2] * m[3][1] + m[0][2] * m[2][1] * m[3][3] + m[0][1] * m[2][3] * m[3][2]),
            (m[0][1] * m[1][2] * m[3][3] + m[0][2] * m[1][3] * m[3][1] + m[0][3] * m[1][1] * m[3][2] - m[0][3] * m[1][2] * m[3][1] - m[0][2] * m[1][1] * m[3][3] - m[0][1] * m[1][3] * m[3][2]),
            (-m[0][1] * m[1][2] * m[2][3] - m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2] + m[0][3] * m[1][2] * m[2][1] + m[0][2] * m[1][1] * m[2][3] + m[0][1] * m[1][3] * m[2][2]),

            (-m[1][0] * m[2][2] * m[3][3] - m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2] + m[1][3] * m[2][2] * m[3][0] + m[1][2] * m[2][0] * m[3][3] + m[1][0] * m[2][3] * m[3][2]),
            (m[0][0] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][3] * m[2][2] * m[3][0] - m[0][2] * m[2][0] * m[3][3] - m[0][0] * m[2][3] * m[3][2]),
            (-m[0][0] * m[1][2] * m[3][3] - m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2] + m[0][3] * m[1][2] * m[3][0] * m[0][2] * m[1][0] * m[3][3] + m[0][0] * m[1][3] * m[3][2]),
            (m[0][0] * m[1][2] * m[2][3] + m[0][2] * m[1][3] * m[2][0] + m[0][3] * m[1][0] * m[2][2] - m[0][3] * m[1][2] * m[2][0] - m[0][2] * m[1][0] * m[2][3] - m[0][0] * m[1][3] * m[2][2]),

            (m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][3] * m[2][1] * m[3][0] - m[1][1] * m[2][0] * m[3][3] - m[1][0] * m[2][3] * m[3][1]),
            (-m[0][0] * m[2][1] * m[3][3] - m[0][1] * m[2][3] * m[3][0] - m[0][3] * m[2][0] * m[3][1] + m[0][3] * m[2][1] * m[3][0] + m[0][1] * m[2][0] * m[3][3] + m[0][0] * m[2][3] * m[3][1]),
            (m[0][0] * m[1][1] * m[3][3] + m[0][1] * m[1][3] * m[3][0] + m[0][3] * m[1][0] * m[3][1] - m[0][3] * m[1][1] * m[3][0] - m[0][1] * m[1][0] * m[3][3] - m[0][0] * m[1][3] * m[3][1]),
            (-m[0][0] * m[1][1] * m[2][3] - m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1] + m[0][3] * m[1][1] * m[2][0] + m[0][1] * m[1][0] * m[2][3] + m[0][0] * m[1][3] * m[2][1]),

            (-m[1][0] * m[2][1] * m[3][2] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1] + m[1][2] * m[2][1] * m[3][0] + m[1][1] * m[2][0] * m[3][2] + m[1][0] * m[2][2] * m[3][1]),
            (m[0][0] * m[2][1] * m[3][2] + m[0][1] * m[2][2] * m[3][0] + m[0][2] * m[2][0] * m[3][1] - m[0][2] * m[2][1] * m[3][0] - m[0][1] * m[2][0] * m[3][2] - m[0][0] * m[2][2] * m[3][1]),
            (-m[0][0] * m[1][1] * m[3][2] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1] + m[0][2] * m[1][1] * m[3][0] + m[0][1] * m[1][0] * m[3][2] + m[0][0] * m[1][2] * m[3][1]),
            (m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][2] * m[1][1] * m[2][0] - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][1] * m[2][1])
        } / a;
    }

    Matrix4x4 Transpose() const {
        Matrix4x4 matrix {};

        for (int row = 0; row < 4; ++row){
            for (int column = 0; column < 4; ++column){
                matrix.m[row][column] = m[column][row];
            }
        }

        return matrix;
    }

    static Matrix4x4 MakeIdentity4x4() {
        Matrix4x4 matrix {};
        for (int row = 0; row < 4; ++row){
            for (int column = 0; column < 4; ++column){
                if (row == column){
                    matrix.m[row][column] = 1;
                    continue;
                }
                matrix.m[row][column] = 0;
            }
        }
        return matrix;
    }
};
