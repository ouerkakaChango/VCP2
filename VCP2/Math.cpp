#include "Math.h"

namespace VCP {
	float DegreeToArc(float degree) {
		return degree / 180.0f*XC_PI;
	}

	float ArcToDegree(float arc) {
		return arc / XC_PI*180.0f;
	}
};