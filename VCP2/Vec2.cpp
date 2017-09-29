#include "Vec2.h"

namespace VCP {

	bool NearlyEqual(const Vec2& v1, const Vec2& v2) {
		return NearlyEqualf(v1.x, v2.x) && NearlyEqualf(v1.y, v2.y);
	}

}

