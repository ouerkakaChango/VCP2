#include "Vec2.h"
#include "Math.h"
namespace VCP {

	bool NearlyEqual(const Vec2& v1, const Vec2& v2) {
		return NearlyEqualf(v1.x, v2.x) && NearlyEqualf(v1.y, v2.y);
	}

	float Dot(const Vec2& v1, const Vec2& v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}

	float Cross(const Vec2& v1, const Vec2& v2) {
		return v1.x*v2.y - v2.x*v1.y;
	}

	float DegreeBetween(const Vec2& v1, const Vec2& v2) {
		return ArcToDegree( acosf(Dot(v1, v2) / v1.len() / v2.len()));
	}
}

