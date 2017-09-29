#include "Camera.h"
namespace VCP {
	 Matrix4_4 Camera::GetPerspectiveProjectionMatrix() const {
		return Matrix4_4(
			a,					0,				0,				 b,
			-(R + L) / (R - L), 2 * N / (R - L),0,				 0,
			-(T + B) / (T - B), 0,				2 * N / (T - B), 0,
			1,					0,				0,				 0);
	}

	 Camera& CameraIns::TemCamera() {
		 static Camera camera;
		 return camera;
	 }
};
