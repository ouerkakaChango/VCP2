#ifndef CAMERA_H
#define CAMERA_H
#include "Math.h"
namespace VCP {
	class Camera{
	public:
		float
			theta = 90.0f,
			N = 10.0f,
			ratio = 1920.0f / 1080.0f;
		float a, b, L, R, B, T, F, height, width, m_tan;
		Camera() {
			F = 1000.0f;//Œﬁ”√
			m_tan = tanf(DegreeToArc(theta / 2));
			width = N*m_tan;
			height = width/ratio;
			a = (F + N) / (F - N);
			b = -2 * N*F / (F - N);
			L = -width;
			R = width;
			B = -height;
			T = height;
		}

		 Matrix4_4 GetPerspectiveProjectionMatrix() const;
	};

	class CameraIns {
	public:
		static Camera& TemCamera();
	};
}
#endif
