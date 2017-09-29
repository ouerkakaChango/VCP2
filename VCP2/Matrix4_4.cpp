#include "Matrix4_4.h"
#include "Math.h"
namespace VCP {

	Matrix4_4 GetRotMatrixByX(float antiClockwiseAngle) {
		float t = DegreeToArc(antiClockwiseAngle);
		return Matrix4_4(
			1, 0,		0,			0,
			0, cos(t),	-sin(t),	0,
			0, sin(t),	cos(t),		0,
			0, 0,		0,			1
		);
	}

	Matrix4_4 GetRotMatrixByY(float antiClockwiseAngle) {
		float t = DegreeToArc(antiClockwiseAngle);
		return Matrix4_4(
			cos(t),		0, sin(t),	0,
			0,			1, 0,		0,
			-sin(t),	0, cos(t),	0,
			0,			0, 0,		1
		);
	}

	Matrix4_4 GetRotMatrixByZ(float antiClockwiseAngle) {
		float t = DegreeToArc(antiClockwiseAngle);
		return Matrix4_4(
			cos(t), -sin(t),	0, 0,
			sin(t), cos(t),		0, 0,
			0,		0,			1, 0,
			0,		0,			0, 1
		);
	}
};
