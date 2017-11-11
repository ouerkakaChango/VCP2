#ifndef VEC2_H
#define VEC2_H
#include "Utility.h"
namespace VCP {
#define NearlyEqualf(a,b) abs((a)-(b))<=0.001f
	class Vec2 {
	public:
		float x, y;
		Vec2(float _x=-99.0f, float _y=-99.0f) :x(_x), y(_y) {}
		Vec2 operator+(const Vec2& v) const{
			return Vec2(x + v.x, y + v.y);
		}
		Vec2 operator-(const Vec2& v) const {
			return Vec2(x - v.x, y - v.y);
		}

		Vec2 operator+=(const Vec2& v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		float len() const {
			return sqrtf(x*x + y*y);
		}
		void Print() const {
			cout << "\n" << x << " " << y;
		}
	};

	bool NearlyEqual(const Vec2& v1, const Vec2& v2);
	float Dot(const Vec2& v1, const Vec2& v2);
	float Cross(const Vec2& v1, const Vec2& v2);
	float DegreeBetween(const Vec2& v1, const Vec2& v2);
}
#endif

