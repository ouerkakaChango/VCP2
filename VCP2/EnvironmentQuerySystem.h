#ifndef ENVIRONMENTQUERYSYSTEM_H
#define ENVIRONMENTQUERYSYSTEM_H
#include "Math.h"
namespace VCP {
	class EnvironmentQuerySystem {
	private:
		EnvironmentQuerySystem() {}
	public:
		static EnvironmentQuerySystem& GetInstance();

		Vec4 GetTargetPos(int targetID);
		Vec4 GetTargetRot(int targetID);
	};
#define EQS EnvironmentQuerySystem::GetInstance()

}
#endif
