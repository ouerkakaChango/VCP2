#ifndef SHOOTTARGET_H
#define SHOOTTARGET_H
namespace VCP {
	class ShootTarget {
	public:
		float x, y, z;
		ShootTarget(const float& _x, const float& _y, const float& _z) :x(_x), y(_y), z(_z) {}
	};
};
#endif
