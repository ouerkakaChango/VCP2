#include "EnvironmentQuerySystem.h"
#include "VCPError.h"
namespace VCP {

	EnvironmentQuerySystem& EnvironmentQuerySystem::GetInstance() {
		static EnvironmentQuerySystem x;
		return x;
	}

	bool EnvironmentQuerySystem::Init(const string& path) {
		cout << "\nEQS Init";
		ifstream ifs;
		ifs.open(path);

		Json::Reader reader;
		if (!reader.parse(ifs, root, false))
		{
			throw VCPError("StoryScript read error,path:" + path);
			return false;
		}


		return true;
	}
#define Jint(x) static_cast<Json::Value::UInt>(x)
	//???
	Vec4 EnvironmentQuerySystem::GetTargetPos(int targetID,int frameID) {
		if (targetID == 0) {
			return Vec4(0, 0, 0);
		}
		else if (targetID == 1) {
			return Vec4(0, 200, 0);
		}
		else {
			auto targetObj = root["shotTargets"][Jint(0)];
			for (auto& iter : root["shotTargets"]) {
				if (iter["id"].asInt() == targetID) {
					targetObj = iter;
				}
			}
			auto frameObj = targetObj["record"][Jint(0)];
			for (auto& iter : targetObj["record"]) {
				if (iter["frameID"].asInt() == frameID) {
					frameObj = iter;
				}
			}
			return Vec4(frameObj["pos"][Jint(0)].asDouble(), frameObj["pos"][Jint(1)].asDouble(), frameObj["pos"][Jint(2)].asDouble());
		}
	}

	//???
	Vec4 EnvironmentQuerySystem::GetTargetRot(int targetID) {
		if (targetID == 0 || targetID == 1) {
			return Vec4(0, 0, 0);
		}
		else {
			//???
			abort();
		}
	}

	//???
	Coordinate3 EnvironmentQuerySystem::GetTargetCoordinate(int targetID, int frameID) {
		if (targetID == 0) {
			return Coordinate3(Vec4(0, 0, 0), Vec4(-1, 0, 0), Vec4(0, -1, 0), Vec4(0, 0, 1));
		}
		else if (targetID == 1) {
			return Coordinate3(Vec4(0, 200, 0), Vec4(-1, 0, 0), Vec4(0, -1, 0), Vec4(0, 0, 1));
		}
	}

}