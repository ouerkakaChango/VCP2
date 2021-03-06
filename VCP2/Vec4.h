#ifndef VEC4_H
#define VEC4_H
#include "Vec2.h"
#include <iostream>
namespace VCP {
	class Vec4 {
	public:
		float x, y, z, w;
		Vec4(const float& _x, const float& _y, const float& _z, const float& _w = 1.0f) :x(_x), y(_y), z(_z), w(_w) {}
		Vec2 xy() const{ return Vec2(x, y); }
		Vec2 yz() const { return Vec2(y, z); }
		Vec4 GetStandardHomogeneous() const{
			return Vec4(x / w, y / w, z / w, 1.0f);
		}

		Vec4 operator-(const Vec4& v) const{
			return Vec4(x-v.x,y-v.y,z-v.z);
		}

		Vec4 operator+(const Vec4& v) const{
			return Vec4(x + v.x, y + v.y, z + v.z);
		}

		Vec4 operator+=(const Vec4& v){
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		//!!!without w
		Vec4 operator*(float n) const{
			return Vec4(x*n, y*n, z*n);
		}
		bool operator==(const Vec4& v) const{
			return NearlyEqualf(x, v.x) && NearlyEqualf(y, v.y) && NearlyEqualf(z, v.z);
		}

		//!!!without w
		Vec4  operator- (void)
		{
			return Vec4(-x,-y,-z);
		};

		bool operator<(const Vec4& v) const {
			if (!NearlyEqualf(x, v.x)) {
				return x < v.x;
			}
			else {
				if (!NearlyEqualf(y, v.y)) {
					return y < v.y;
				}
				else  {
					if (!NearlyEqualf(z, v.z)) {
						return z < v.z;
					}
					else {
						return false;
					}
				}
			}
		}

		float len() const {
			return sqrtf(x*x + y*y + z*z);
		}
		void Print() const{
			std::cout <<"\n" <<x << " " << y << " " << z << " " << w;
		}
	};

	bool NearlyEqual(const Vec4& v1, const Vec4& v2);
	
};
#endif
