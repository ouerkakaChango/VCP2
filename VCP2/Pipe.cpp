#include "Pipe.h"
#include "VCPError.h"
#include "Utility.h"
namespace VCP {

	void PipeNode::PumpStart() {
		if (frontNode != nullptr) {
			filiterFunction(frontNode->outputDataVec, inputDataVec);
		}
		calculateFunction(inputDataVec,outputDataVec);
		if (backNode != nullptr) {
			backNode->PumpStart();
		}
		else {
			//告诉pipe我以完成
			pipe->NotifyDone();
		}
	}

	void PipeNode::FiliterStart(const vector<PipeData>& startData) {
		filiterFunction(startData, inputDataVec);
	}

	void PipeBase::PumpStart() {
		if (nodeVec.empty()) {
			throw VCPError("PipeNode empty");
		}
		else {
			nodeVec[0]->inputDataVec = startDataVec;
			nodeVec[0]->PumpStart();
		}
	}

}