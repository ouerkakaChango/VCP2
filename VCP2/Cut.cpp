#include "Cut.h"
#include "TransFunction.h"
#include "Utility.h"
#include "VCPError.h"
#include <algorithm>
#include <iterator>
namespace VCP {
	


	void CutPipe::Assemble() {
		PipeNode* p1 = new PipeNode();
		p1->inputDataVec.push_back(PipeData("start","localOffset"));
		p1->inputDataVec.push_back(PipeData("start","rot"));

		p1->outputDataVec.push_back(PipeData("CutPipe_p1", "dvec"));

		p1->filiterFunction = [](vector<PipeData> frontOutputDataVec, vector<PipeData>& temInputDataVec) {
			temInputDataVec[0].data = frontOutputDataVec[0].data;
			temInputDataVec[1].data = frontOutputDataVec[1].data;
			//Vec4* rot = (Vec4*)temInputDataVec[1].data;
			//rot->Print();
		};
		p1->calculateFunction = [](vector<PipeData> temInputDataVec,vector<PipeData>& temOutputDataVec) {
			Vec4* localOffset =static_cast<Vec4*>(temInputDataVec[0].data);
			Vec4* rot = static_cast<Vec4*>(temInputDataVec[1].data);
			//Vec4 dvec = GetRotated(*localOffset, *rot);
			//dvec.Print();
			temOutputDataVec[0].data = (void*)new Vec4(GetRotated(*localOffset, *rot));
		};
		///

		PipeNode* p2 = new PipeNode();
		p2->inputDataVec.push_back(PipeData("front", "dvec"));
		p2->inputDataVec.push_back(PipeData("start", "s1"));
		p2->inputDataVec.push_back(PipeData("start", "s2"));

		p2->outputDataVec.push_back(PipeData("CutPipe_p2", "t1t2"));

		p2->filiterFunction = [this](vector<PipeData> frontOutputDataVec, vector<PipeData>& temInputDataVec) {
			temInputDataVec[0].data = frontOutputDataVec[0].data;
			//这里可以根据名字自动找，先不实现
			temInputDataVec[1].data = startDataVec[2].data;//s1
			temInputDataVec[2].data = startDataVec[3].data;//s2
		};

		p2->calculateFunction = [](vector<PipeData> temInputDataVec, vector<PipeData>& temOutputDataVec) {
			Vec4* dvec = static_cast<Vec4*>(temInputDataVec[0].data);
			Vec2* s1= static_cast<Vec2*>(temInputDataVec[1].data);
			Vec2* s2 = static_cast<Vec2*>(temInputDataVec[2].data);
			temOutputDataVec[0].data = (void*)new Vec2(GetT1T2(*dvec, *s1, *s2, CameraIns::TemCamera()));
		};
		///

		PipeNode* p3 = new PipeNode();
		p3->inputDataVec.push_back(PipeData("front", "s1"));
		p3->inputDataVec.push_back(PipeData("front", "t1"));

		p3->outputDataVec.push_back(PipeData("Cut_p3", "cpos"));

		p3->filiterFunction = [this](vector<PipeData> frontOutputDataVec, vector<PipeData>& temInputDataVec) {
			temInputDataVec[0].data = startDataVec[2].data;//s1
			Vec2* t1t2 = static_cast<Vec2*>(frontOutputDataVec[0].data);
			temInputDataVec[1].data = (void*)&t1t2->x;//t1
		};

		p3->calculateFunction = [](vector<PipeData> temInputDataVec, vector<PipeData>& temOutputDataVec) {
			Vec2* s1 = static_cast<Vec2*>(temInputDataVec[0].data);
			float* t1= static_cast<float*>(temInputDataVec[1].data);
			temOutputDataVec[0].data = (void*)new Vec4(GetCPosBySpos(*s1, CameraIns::TemCamera(), *t1));
			//Vec4*p = static_cast<Vec4*>(temOutputDataVec[0].data);
			//p->Print();
		};
		///

		p1->pipe = this;
		p2->pipe = this;
		p3->pipe = this;

		p1->frontNode = nullptr;
		p2->frontNode = p1;
		p3->frontNode = p2;

		p1->backNode = p2;
		p2->backNode = p3;
		p3->backNode = nullptr;

		nodeVec.push_back(p1);
		nodeVec.push_back(p2);
		nodeVec.push_back(p3);
	}

	void CutPipe::NotifyDone() {
		if (cloud != nullptr) {
			cloud->NotifyDone();
		}
	}

	void CutPipe::PrintOutput() {
		Vec4* cpos = (Vec4*)nodeVec.back()->outputDataVec[0].data;
		cpos->Print();
	}
	void CutPipe::InitInput(const CutInputData& input) {
		startDataVec.push_back(PipeData("start", "localOffset", (void*)&input.localOffset));
		startDataVec.push_back(PipeData("start", "rot", (void*)&input.rot));
		startDataVec.push_back(PipeData("start", "s1", (void*)&input.s1));
		startDataVec.push_back(PipeData("start", "s2", (void*)&input.s2));
	}

	void CutInputCloud::GenerateFuzzyCloud() {
		//???
		Vec4 drot = Vec4(10.0f, 10.0f, 10.0f);
		Vec4 ddrot = Vec4(1.0f, 1.0f, 1.0f);
		Vec2 ds = Vec2(0.0f, 0.3f);
		Vec2 dds = Vec2(0.0f, 0.05f);
		for (Vec4 rot = baseData.rot - drot; !NearlyEqual(rot, baseData.rot + drot); rot += ddrot) {
			for (Vec2 s1 = baseData.s1 - ds; !NearlyEqual(s1, baseData.s1 + ds); s1 += dds) {
				for (Vec2 s2 = baseData.s2 - ds; !NearlyEqual(s2, baseData.s2 + ds); s2 += dds) {
					bool t= NearlyEqual(s2, baseData.s2 + ds);
					
					//...计算评分
					float tem = 1 / 3.0 * (
						(1.0f - (rot - baseData.rot).len() / (10.0f * sqrtf(3.0f))) +
						(1.0f - (s2 - baseData.s2).len() / (0.1f*sqrtf(2.0f))) +
						(1.0f - (s1 - baseData.s1).len() / (0.1f*sqrtf(2.0f)))
						);
					dataVec.push_back(CutInputData(baseData.localOffset, rot, s1, s2));
					rateVec.push_back(tem);
				}
			}
		}

	}

	void CutInputCloud::GenerateSurroundCloud() {
		Vec4 maxrot(0.0f, 0.0f, 359.0f);
		for (Vec4 rot = baseData.rot; rot < maxrot; rot.z += 1.0f) {
			dataVec.push_back(CutInputData(baseData.localOffset, rot, baseData.s1, baseData.s2));
			rateVec.push_back(1.0f);
		}
	}

	void CutOutputCloud::TransToWorldCoo(const Vec4& objPos, const Vec4& objRot) {
		//???
		for (auto& iter : dataVec) {
			iter.centerCPos = objPos- GetRotMatrixByZ(objRot.z+iter.rot.z)*(GetRotMatrixByY(-objRot.y )*(GetRotMatrixByX(-objRot.x)*iter.centerCPos));

			//iter.rot = objRot;
		}
	}

	void CutOutputCloud::SetRateAndToFile(const string& path) {
		std::ofstream outfile;
		outfile.open(path);
		if (!outfile.is_open()) { throw VCPError("File open error"); }
		else {
			for (int i = 0; i < (int)dataVec.size(); i++) {
				dataVec[i].rate = inputCloud->rateVec[i];
				outfile << dataVec[i].centerCPos.x << " " << dataVec[i].centerCPos.y << " " << dataVec[i].centerCPos.z << " " \
					<< dataVec[i].rot.x << " " << dataVec[i].rot.y << " " << dataVec[i].rot.z << " " << dataVec[i] .rate<<"\n";
			}
		}
		outfile.close();
		cout << "\n======ToFileDONE======";
	}

	CutPipeCloud::CutPipeCloud(const CutInputCloud& _inputCloud):
	inputCloud(&_inputCloud)
	{
		for (int i = 0; i < (int)_inputCloud.dataVec.size(); i++) {
			CutPipe* p = new CutPipe();
			p->InitInput(_inputCloud.dataVec[i]);
			p->Assemble();
			p->cloud = this;
			pipeVec.push_back(p);
		}
		outputCloud.inputCloud = inputCloud;
	}

	void CutPipeCloud::PumpStart() {
		//common mode
		/*for (auto& iter : pipeVec) {
			iter->PumpStart();
		}*/

		//muti-thread mode
		for (int i = 0; i < (int)pipeVec.size();i++) {
			threadVec.push_back(thread(std::mem_fn(&CutPipe::PumpStart), pipeVec[i]));
			threadVec[i].join();
		}
	}

	void CutPipeCloud::NotifyDone() {
		nowDoneNum += 1;
		if (nowDoneNum == pipeVec.size()) {
			EndWork();
		}
	}

	void CutPipeCloud::EndWork() {
		cout << "\n======CalculationDONE======";
		for (auto& pipeiter : pipeVec) {
			Vec4* ori = (Vec4*)pipeiter->nodeVec.back()->outputDataVec[0].data;
			Vec4 temcpos = Vec4((int)ori->x, (int)ori->y, (int)ori->z);
			Vec4* temrot = (Vec4*)pipeiter->nodeVec[0]->inputDataVec[1].data;
			CutOutPutData tem = CutOutPutData(temcpos, *temrot);
			if (std::find(outputCloud.dataVec.begin(), outputCloud.dataVec.end(), tem) == outputCloud.dataVec.end()) {
				outputCloud.dataVec.push_back(tem);
			}
		}
		cout<< "\n======OutValueAdjustDONE======";
		//改动部分
		outputCloud.TransToWorldCoo(Vec4(0, 0, 0), Vec4(0, 0, 0));
		outputCloud.SetRateAndToFile("D:\\VCP3.txt");
	}

	///

	void CutCloudSet::InitByFile(const string& path) {
		std::ifstream infile(path);
		string temline;
		if (infile) {
			while (std::getline(infile, temline)) // line中不包括每行的换行符  
			{
				//cout << "\n" << temline;
				lineVec.push_back(temline);
			}
		}
		else {
			throw VCPError("File read error.");
		}

		
		int flag = 0;
		string tem="";
		float px, py, pz, rx, ry, rz;
		float rate;

		for (auto& line : lineVec) {
			flag = 0;
			for (int i = 0; i < (int)line.size(); i++) {
				if (line[i] == ' ' || i == (line.size() - 1)) {
					if (i == (line.size() - 1)) {
						tem += line[i];
						rate = stringToNum<float>(tem);
					}
					else if (flag == 0) {
						px = stringToNum<float>(tem);
					}
					else if (flag == 1) {
						py = stringToNum<float>(tem);
					}
					else if (flag == 2) {
						pz = stringToNum<float>(tem);
					}
					else if (flag == 3) {
						rx = stringToNum<float>(tem);
					}
					else if (flag == 4) {
						ry = stringToNum<float>(tem);
					}
					else if (flag == 5) {
						rz = stringToNum<float>(tem);
					}
					else {
						throw VCPError("Flag error.");
					}
					tem = "";
					flag++;
				}
				else {
					tem += line[i];
				}
			}//for line
			//outVec.push_back(CutOutPutData(Vec4(px,py,pz), Vec4(rx,ry,rz)));
			outSet.insert(*(new CutOutPutData(Vec4(px, py, pz), Vec4(rx, ry, rz),rate)));
		}
		cout << " " << outSet.size();
	}//CutCloudSet::InitByFile end

	void CutCloudSet::IntersectionAndToFile(const CutCloudSet& set2, const string& outpath) {
		set<CutOutPutData> inter;
		std::set_intersection(outSet.begin(), outSet.end(), set2.outSet.begin(), set2.outSet.end(), std::inserter(inter, inter.end()));
		cout <<"\n" << inter.size();
	/*	for (auto& iter : i) {
			cout << "\n*********";
			iter.centerCPos.Print();
			iter.rot.Print();
		}*/
		std::ofstream outfile;
		outfile.open(outpath);
		if (!outfile.is_open()) { throw VCPError("File open error"); }
		else {
			for (auto& it:inter) {
				outfile << it.centerCPos.x << " " << it.centerCPos.y << " " << it.centerCPos.z << " " << \
					it.rot.x << " " << it.rot.y << " " << it.rot.z << " " << \
					it.rate << "\n";
				//这里的rate需要重新计算，比如取平均值，目前就先不计算了
			}
		}
		outfile.close();
	}//CutCloudSet::IntersectionAndToFile

}