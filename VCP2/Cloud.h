#ifndef CLOUD_H
#define CLOUD_H
#include "Utility.h"
namespace VCP {
	class Cloud {};

	class InputCloudBase {
	public:
		
	};

	class OutputCloudBase {
	public:
		
	};

	class PipeCloudBase {
	public:
		virtual void PumpStart() = 0;
		virtual void NotifyDone() = 0;
		virtual void EndWork() = 0;
		int nowDoneNum = 0;
	};
}
#endif

