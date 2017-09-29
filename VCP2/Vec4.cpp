#include "Vec4.h"
namespace VCP {
	bool NearlyEqual(const Vec4& v1, const Vec4& v2) {
		return NearlyEqualf(v1.x, v2.x) && NearlyEqualf(v1.y, v2.y) && NearlyEqualf(v1.z, v2.z);
	}

}
