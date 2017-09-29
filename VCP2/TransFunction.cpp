#include "TransFunction.h"
#include "VCPError.h"
namespace VCP {
	Vec2 GetScreenPos(const Camera& camera, Vec4 pos) {
		//!!!
		auto m = camera.GetPerspectiveProjectionMatrix();
		//std::cout << m.value[0][0] << m.value[0][1] << m.value[0][2] << m.value[0][3] ;
		(camera.GetPerspectiveProjectionMatrix()*pos).Print();
		//std::cout<<"\n"<<tan(45.0f);
		Vec2 re=(camera.GetPerspectiveProjectionMatrix()*pos).GetStandardHomogeneous().yz();
		NearAdjust(re.x, 1.0, >= );
		NearAdjust(re.x, -1.0, <= );
		NearAdjust(re.y, 1.0, >= );
		NearAdjust(re.y, -1.0, <= );
		if (re.x > 1.0f || re.x<-1.0f || re.y>1.0f || re.y < -1.0f) {
			throw VCPError("OutOfScreen,cannot be seen");
		}
		return re;
	}

	Vec4 GetCPosBySpos(const Vec2& s1, const Camera& camera, const float& t) {
		return Vec4(t, s1.x*camera.m_tan*t, s1.y/camera.ratio*camera.m_tan*t);
	}

	Vec4 GetRotated(const Vec4& vec, const Vec4& rot) {
		return GetRotMatrixByZ(rot.z)*(GetRotMatrixByY(-rot.y)*(GetRotMatrixByX(-rot.x)*vec));
	}

	Vec2 GetT1T2(const Vec4& dvec, const Vec2& s1, const Vec2& s2, const Camera& camera) {
		float t1=-999, t2=-999;
		if (!NearlyEqualf(s1.x, s2.x)) {
			t2 = (dvec.y - camera.m_tan*s1.x*dvec.x) / (camera.m_tan*(s2.x - s1.x));
		}
		else if (!NearlyEqualf(s1.y, s2.y)) {
			t2 = (dvec.z - camera.m_tan / camera.ratio*s1.y*dvec.x) / (camera.m_tan / camera.ratio*(s2.y - s1.y));
		}
		else {
			throw VCPError("Warning:s1,s2 NearlyEqual");
		}
		t1 = t2 - dvec.x;
		return Vec2(t1, t2);
	}
};
