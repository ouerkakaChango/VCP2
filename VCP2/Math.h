#ifndef MATH_H
#define MATH_H
#include "Matrix4_4.h"
#include "Vec2.h"
#include "Vec4.h"
#include "Coordinate3.h"
#include <math.h>
namespace VCP {
#define XC_PI 3.1415926f
#define NearAdjust(num,standard,comparer) \
	if ((num) comparer (standard)&&NearlyEqualf(num, standard)) { \
		(num) = (standard); \
	}

	class Math {
	public:

	};

	float DegreeToArc(float degree);
	float ArcToDegree(float arc);
};
#endif

