#ifndef VEC2_H
#define VEC2_H
#include <iostream>
using std::cout;
namespace VCP {
#define NearlyEqualf(a,b) abs((a)-(b))<=0.001f
	class Vec2 {
	public:
		float x, y;
		Vec2(float _x, float _y) :x(_x), y(_y) {}
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
};
#endif

