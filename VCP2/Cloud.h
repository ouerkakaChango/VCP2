#ifndef CLOUD_H
#define CLOUD_H
#include "Utility.h"
namespace VCP {
	class Cloud {};

	class InputCloudBase {
	public:
		std::function<void()> generateFuzzyCloudFunction;
	};

	class OutputCloudBase {
	public:
		
	};
	class PipeCloudBase {
	public:
		virtual void PumpStart() = 0;
		virtual void NotifyDone() = 0;
		std::function<void()> endFunction;
		int nowDoneNum = 0;
	};
}
#endif

