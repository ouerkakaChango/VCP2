#ifndef MATRIX4_4_H
#define MATRIX4_4_H
#include "Vec4.h"
namespace VCP {
	class Matrix4_4 {
	public:
		float value[4][4];
		Matrix4_4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33
		) {
			value[0][0] = m00; value[0][1] = m01; value[0][2] = m02; value[0][3] = m03;
			value[1][0] = m10; value[1][1] = m11; value[1][2] = m12; value[1][3] = m13;
			value[2][0] = m20; value[2][1] = m21; value[2][2] = m22; value[2][3] = m23;
			value[3][0] = m30; value[3][1] = m31; value[3][2] = m32; value[3][3] = m33;
		}
		Matrix4_4() {}
		const Vec4 operator*(const Vec4& v4) {
			return Vec4(
				value[0][0] * v4.x + value[0][1] * v4.y + value[0][2] * v4.z + value[0][3] * v4.w,
				value[1][0] * v4.x + value[1][1] * v4.y + value[1][2] * v4.z + value[1][3] * v4.w,
				value[2][0] * v4.x + value[2][1] * v4.y + value[2][2] * v4.z + value[2][3] * v4.w,
				value[3][0] * v4.x + value[3][1] * v4.y + value[3][2] * v4.z + value[3][3] * v4.w
			);
		}

		const Matrix4_4 operator*(const Matrix4_4& m) {
			Matrix4_4 re;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					re.value[i][j] = \
						value[i][0] * m.value[0][j] + \
						value[i][1] * m.value[1][j] + \
						value[i][2] * m.value[2][j] + \
						value[i][3] * m.value[3][j];
				}
			}
			return re;
		}
	};

	//可优化

	//看向x轴正方向，逆时针
	Matrix4_4 GetRotMatrixByX(float antiClockwiseAngle);
	//看向Y轴正方向，逆时针
	Matrix4_4 GetRotMatrixByY(float antiClockwiseAngle);
	//看向z轴正方向，逆时针
	Matrix4_4 GetRotMatrixByZ(float antiClockwiseAngle);
};
#endif

