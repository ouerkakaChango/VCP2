#include "EnvironmentQuerySystem.h"
namespace VCP {

	EnvironmentQuerySystem& EnvironmentQuerySystem::GetInstance() {
		static EnvironmentQuerySystem x;
		return x;
	}
	//???
	Vec4 EnvironmentQuerySystem::GetTargetPos(int targetID) {
		if (targetID == 0) {
			return Vec4(0, 0, 0);
		}
		else if (targetID == 1) {
			return Vec4(0, 200, 0);
		}
	}
	Vec4 EnvironmentQuerySystem::GetTargetRot(int targetID) {
		return Vec4(0, 0, 0);
	}

}