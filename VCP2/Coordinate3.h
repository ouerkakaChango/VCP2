#ifndef COORDINATE3_H
#define COORDINATE3_H
#include "Vec4.h"
namespace VCP {
	class Coordinate3 {
	public:
		Vec4 origin,xdir, ydir, zdir;
		Coordinate3(const Vec4& _origin=Vec4(-99.0f,-99.0f,-99.0f), \
			const Vec4& _xdir = Vec4(-99.0f, -99.0f, -99.0f), \
			const Vec4& _ydir = Vec4(-99.0f, -99.0f, -99.0f), \
			const Vec4& _zdir = Vec4(-99.0f, -99.0f, -99.0f)) :
			origin(_origin), xdir(_xdir), ydir(_ydir), zdir(_zdir) {}
	};

}
#endif

