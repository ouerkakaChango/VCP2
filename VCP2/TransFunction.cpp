#include "TransFunction.h"
#include "VCPError.h"
namespace VCP {
	Vec2 GetScreenPos(const Camera& camera, Vec4 pos) {
		//!!!
		auto m = camera.GetPerspectiveProjectionMatrix();
		//std::cout << m.value[0][0] << m.value[0][1] << m.value[0][2] << m.value[0][3] ;
		//(camera.GetPerspectiveProjectionMatrix()*pos).Print();
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
		//return GetRotMatrixByZ(rot.z)*(GetRotMatrixByY(-rot.y)*(GetRotMatrixByX(-rot.x)*vec));
		return vec;
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

	Vec4 CooTrans(const Coordinate3& cbase, const Coordinate3& c2, Vec4 vecInC2) {
		return c2.origin + c2.xdir*vecInC2.x+c2.ydir*vecInC2.y+c2.zdir*vecInC2.z;
	}

	Coordinate3 RevertInfo(Coordinate3 baseCoo, Vec4 pos, Vec4 rot) {
		Coordinate3 re;
		Vec4 txdir=Vec4(-1,0,0), tydir = Vec4(0, -1, 0), tzdir = Vec4(0, 0, 1);
		//遵循zxy顺规旋转
		Matrix4_4 M3R = GetRotMatrixByY(-rot.y)*(GetRotMatrixByX(-rot.x)*GetRotMatrixByZ(-rot.z));
		//z
		txdir = GetRotMatrixByZ(-rot.z)*txdir;
		tydir = GetRotMatrixByZ(-rot.z)*tydir;
		//x
		tydir = GetRotMatrixByX(-rot.x)*tydir;
		tzdir = GetRotMatrixByX(-rot.x)*tzdir;
		//y
		txdir = GetRotMatrixByY(-rot.y)*txdir;
		tzdir = GetRotMatrixByY(-rot.y)*tzdir;

		Vec4 px(pos.x, 0, 0), py(0, pos.y, 0), pz(0, 0, -pos.z);
		//z
		px = GetRotMatrixByZ(-rot.z)*px;
		py = GetRotMatrixByZ(-rot.z)*py;
		//x
		py = GetRotMatrixByX(-rot.x)*py;
		pz = GetRotMatrixByX(-rot.x)*pz;
		//y
		px = GetRotMatrixByY(-rot.y)*px;
		pz = GetRotMatrixByY(-rot.y)*pz;
		
		Vec4 op = px + py + pz;


		/*txdir.Print();
		tydir.Print();
		tzdir.Print();
		op.Print();*/

		re.origin = op;
		re.xdir = txdir;
		re.ydir = tydir;
		re.zdir = tzdir;
		return re;
	}

	Vec4 GetWR(Coordinate3 worldCoo, Coordinate3 ObjCoo, Coordinate3 cameraCooInObjCoo) {
		
		Vec4 txdir = CooTrans(worldCoo, ObjCoo, cameraCooInObjCoo.xdir)- ObjCoo.origin;
		Vec4 tydir = CooTrans(worldCoo, ObjCoo, cameraCooInObjCoo.ydir) - ObjCoo.origin;
		Vec4 tzdir = CooTrans(worldCoo, ObjCoo, cameraCooInObjCoo.zdir) - ObjCoo.origin;

		/*txdir.Print();
		tydir.Print();
		tzdir.Print();*/

		Vec2 v1(0, 1);
		Vec2 v2;
		//roll=a
		v2.x = tzdir.y;
		v2.y = tzdir.z;
		float a = DegreeBetween(v1, v2);
		if (Cross(v2, v1) > 0.0f) {
			//不变
		}
		else {
			a = 360.0f - a;
		}

		//pitch=b
		v2.x = tzdir.x;
		v2.y = tzdir.z;
		float b = DegreeBetween(v1, v2);
		if (Cross(v2, v1) < 0.0f) {
			//不变
		}
		else {
			b = 360.0f - b;
		}

		//yaw=c
		v2.x = txdir.y;
		v2.y = txdir.x;
		float c = DegreeBetween(v1, v2);
		if (Cross(v2, v1) > 0.0f) {
			//不变
		}
		else {
			c = 360.0f - c;
		}
		if (NearlyEqualf(a, 360.0f)) { a = 0.0f; }
		if (NearlyEqualf(b, 360.0f)) { b = 0.0f; }
		if (NearlyEqualf(c, 360.0f)) { c = 0.0f; }
		return Vec4(a, b, c);
	}

}
