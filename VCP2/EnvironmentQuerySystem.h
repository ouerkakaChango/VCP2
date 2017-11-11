#ifndef ENVIRONMENTQUERYSYSTEM_H
#define ENVIRONMENTQUERYSYSTEM_H
#include "Math.h"
#include "Utility.h"
#include "json.h"
namespace VCP {
	class EnvironmentQuerySystem {
	private:
		EnvironmentQuerySystem() {}
		Json::Value root;
	public:
		static EnvironmentQuerySystem& GetInstance();
		bool Init(const string& path);
		Vec4 GetTargetPos(int targetID,int frameID=0);
		Vec4 GetTargetRot(int targetID);
		Coordinate3 GetTargetCoordinate(int targetID, int frameID=0);
	};
#define EQS EnvironmentQuerySystem::GetInstance()

}
#endif
