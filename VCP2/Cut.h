#ifndef CUT_H
#define CUT_H
#include "Math.h"
#include "Pipe.h"
#include "Cloud.h"
#include <thread>
#include <set>
using std::thread;
using std::set;
namespace VCP {
	class Cut{};

	class CutInputData {
	public:
		Vec4 localOffset, rot;
		Vec2 s1, s2;
		CutInputData(const Vec4& _localOffset, const Vec4& _rot, const Vec2& _s1, const Vec2& _s2) :
			localOffset(_localOffset),
			rot(_rot),
			s1(_s1),
			s2(_s2) {}

		//CutInputData(const CutInputData& x) = delete;
		//CutInputData(CutInputData&& x) = delete;
	};
	class CutOutPutData {
	public:
		Vec4 centerCPos;
		Vec4 rot;
		float rate;

		CutOutPutData(const Vec4& cpos = Vec4(-99.0f, -99.0f, -99.0f),const Vec4& _rot = Vec4(-99.0f, -99.0f, -99.0f),const float& _rate=-1.0f) :
			centerCPos(cpos) ,
			rot(_rot),
			rate(_rate){}

		bool operator==(const CutOutPutData& v) const{
			return centerCPos == v.centerCPos&&rot==v.rot;
		}

		bool operator<(const CutOutPutData& v) const {
			if (!(centerCPos == v.centerCPos)) {
				return centerCPos < v.centerCPos;
			}
			else {
				if (!(rot == v.rot)) {
					return rot < v.rot;
				}
				else {
					return rate<v.rate;
				}
			}
			
		}
	};

	class CutPipeCloud;

	class CutPipe :public PipeBase {
	public:
		CutPipeCloud *cloud=nullptr;
		virtual void Assemble() override;
		virtual void PrintOutput() override;
		virtual void NotifyDone() override;
		void InitInput(const CutInputData& input);
	};

	class CutInputCloud :public InputCloudBase {
	public:
		vector<float> rateVec;
		vector<CutInputData> dataVec;
		CutInputData baseData;
		CutInputCloud(const CutInputData& _baseData) :
			baseData(_baseData) {}
		void Print() const {
			for (auto&i : dataVec) {
				cout << "\n#########################"; 
				i.localOffset.Print(); 
				i.rot.Print();
				i.s1.Print();
				i.s2.Print();;
			}
		}
	};

	class CutOutputCloud :public OutputCloudBase{
	public:
		vector<CutOutPutData> dataVec;
		const CutInputCloud* inputCloud;
		void TransToWorldCoo1(const Vec4& objPos, const Vec4& objRot);
		void TransToWorldCoo2(const Vec4& objPos, const Vec4& objRot);
		 void SetRateAndToFile(const string& path);
	};

	class CutPipeCloud :public PipeCloudBase {
	public:
		vector<thread> threadVec;
		vector<CutPipe*> pipeVec;
		CutOutputCloud outputCloud;
		const CutInputCloud* inputCloud;
		CutPipeCloud(const CutInputCloud& _inputCloud);
		virtual void PumpStart() override;
		virtual void NotifyDone() override;
	};

	///

	class CutCloudSet {
	public:
		vector<string> lineVec;
		set<CutOutPutData> outSet;
		vector<CutOutPutData> outVec;
		void InitByFile(const string& path);
		void InitVecByFile(const string& path);
		void IntersectionAndToFile(const CutCloudSet& set2,const string& outpath);
	};
}
#endif

