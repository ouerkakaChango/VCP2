#ifndef TRANSFUNCTION_H
#define TRANSFUNCTION_H
#include "Math.h"
#include "Camera.h"
#include "ShootTarget.h"
namespace VCP {
	class TransFunction {
	public:
	};

	Vec2 GetScreenPos(const Camera& camera, Vec4 pos);
	Vec4 GetCPosBySpos(const Vec2& s1, const Camera& camera, const float& t);
	Vec4 GetRotated(const Vec4& vec, const Vec4& rot);
	Vec2 GetT1T2(const Vec4& dvec, const Vec2& s1, const Vec2& s2, const Camera& camera);
};
#endif

