#ifndef PIPE_H
#define PIPE_H
#include "Utility.h"
namespace VCP {
	class Pipe {};

	#define PipeNodeFiliter function<void(vector<PipeData>,vector<PipeData>&)>
	#define PipeNodeCaculator function<void(vector<PipeData>,vector<PipeData>&)>

	class PipeData {
	public:
		void* data;
		string name;
		string source;
		PipeData(const string& _source, const string& _name="NULL",void* _data = nullptr) :
			source(_source),
			name(_name),
			data(_data) {}

		//PipeData(const PipeData& x) = delete;
		//PipeData(PipeData&& x) = delete;
	};

	class PipeBase;

	class PipeNode {
	public:
		vector<PipeData> inputDataVec, outputDataVec;
		PipeBase *pipe;
		PipeNode *frontNode,*backNode;
		PipeNodeFiliter filiterFunction;
		PipeNodeCaculator calculateFunction;
		void PumpStart();
		void FiliterStart(const vector<PipeData>& startData);
	};

	class PipeBase {
	public:
		vector<PipeData> startDataVec;
		vector<PipeNode*> nodeVec;
		virtual void NotifyDone() = 0;
		virtual void Assemble() = 0;
		virtual void PrintOutput() = 0;
		void PumpStart();
	};
}
#endif

