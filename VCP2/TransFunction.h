#ifndef TRANSFUNCTION_H
#define TRANSFUNCTION_H
#include "Math.h"
#include "Camera.h"
#include "Coordinate3.h"
namespace VCP {
	class TransFunction {
	public:
	};

	//@pos,是相机坐标系下的pos
	Vec2 GetScreenPos(const Camera& camera, Vec4 pos);
	Vec4 GetCPosBySpos(const Vec2& s1, const Camera& camera, const float& t);
	Vec4 GetRotated(const Vec4& vec, const Vec4& rot);
	Vec2 GetT1T2(const Vec4& dvec, const Vec2& s1, const Vec2& s2, const Camera& camera);
	Vec4 CooTrans(const Coordinate3& cbase, const Coordinate3& c2, Vec4 vecInC2);
	Coordinate3 RevertInfo(Coordinate3 baseCoo, Vec4 pos, Vec4 rot);
	Vec4 GetWR(Coordinate3 worldCoo, Coordinate3 ObjCoo, Coordinate3 cameraCooInObjCoo);
	Vec4 GetEulerAngleWR0YZ(Vec4 vec);
};
#endif

