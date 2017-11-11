#pragma comment(lib, "jsoncpp_d86.lib")

#include "json.h"
#include "ShotScript.h"
#include "VCPError.h"
#include "Math.h"
#include "Cut.h"
#include "EnvironmentQuerySystem.h"
#include "TransFunction.h"
#include <random>

namespace VCP {
#define Jint(x) static_cast<Json::Value::UInt>(x)
	ShotScript::ShotScript(const string& filepath) {
		ifstream ifs;
		ifs.open(filepath);

		Json::Reader reader;
		Json::Value root;
		if (!reader.parse(ifs, root, false))
		{
			throw VCPError("ShotScript read error,path:"+filepath);
		}

		//全局变量
		int flagFrame = 0;
		int	fps = root["fps"].asInt();
		ofstream ofile;
		ofile.open("D:\\VCP2\\testFrameFile.txt");

		Json::Value shotArr = root["shot"];
		for (auto& tshot : shotArr) {

			//每镜头全局变量
			int id = tshot["id"].asInt();
			int type = tshot["type"].asInt();
			int fuzzyMethod = tshot["fuzzyMethod"].asInt();
			Json::Value tparams = tshot["parameters"];
			Json::Value tfparams = tshot["fuzzyParameters"];
			int startFrameID = flagFrame + 1;
			int endFrameID = flagFrame + static_cast<int>(fps*tshot["duration"].asDouble());
			flagFrame = endFrameID;

			//镜头类型判断
			if (type == 0) {
				//Cut
				cout << "\nCut";
				int targetNum = tparams["target"].size();
				auto localOffsetArr = tparams["localOffset"];
				for (int i = 0; i < targetNum; i++) {
					//???
					//缺省参数自动设定还未写
#define JGet(name,index) tparams[name][i][Jint(index)].asDouble()
					Vec4 M_vec(JGet("localOffset",0), JGet("localOffset", 1), JGet("localOffset", 2)),
						rot(JGet("rot", 0), JGet("rot", 1), JGet("rot", 2));
					Vec2 s1(JGet("s1", 0), JGet("s1", 1)), s2(JGet("s2", 0), JGet("s2", 1));

					M_vec.Print();
					rot.Print();
					s1.Print();
					s2.Print();
					CutInputData input(M_vec,rot,s1,s2);
					CutInputCloud inputcloud(input);
	
					if (fuzzyMethod == 0) {
					inputcloud.generateFuzzyCloudFunction = [&]() {
#define JFGet(name,index) tfparams[name][Jint(index)].asDouble()
							Vec4 drot = Vec4(JFGet("drot",0), JFGet("drot", 1), JFGet("drot", 2));
							Vec4 ddrot = Vec4(JFGet("ddrot", 0), JFGet("ddrot", 1), JFGet("ddrot", 2));
							Vec2 ds = Vec2(JFGet("ds", 0), JFGet("ds", 1));
							Vec2 dds = Vec2(JFGet("dds", 0), JFGet("dds", 1));
							//JFGet里name写错的话,jsoncpp是不会抛异常的！！！
							drot.Print();
							ddrot.Print();
							ds.Print();
							dds.Print();
							for (Vec4 rot = inputcloud.baseData.rot - drot; !NearlyEqual(rot, inputcloud.baseData.rot + drot); rot += ddrot) {
								for (Vec2 s1 = inputcloud.baseData.s1 - ds; !NearlyEqual(s1, inputcloud.baseData.s1 + ds); s1 += dds) {
									for (Vec2 s2 = inputcloud.baseData.s2 - ds; !NearlyEqual(s2, inputcloud.baseData.s2 + ds); s2 += dds) {
										bool t = NearlyEqual(s2, inputcloud.baseData.s2 + ds);

										//...计算评分
										float tem = 1 / 3.0 * (
											(1.0f - (rot - inputcloud.baseData.rot).len() / (10.0f * sqrtf(3.0f))) +
											(1.0f - (s2 - inputcloud.baseData.s2).len() / (0.1f*sqrtf(2.0f))) +
											(1.0f - (s1 - inputcloud.baseData.s1).len() / (0.1f*sqrtf(2.0f)))
											);
										inputcloud.dataVec.push_back(CutInputData(inputcloud.baseData.localOffset, rot, s1, s2));
										inputcloud.rateVec.push_back(tem);
									}
								}
							}
						};

					}
					else {
						throw VCPError("FuzzyMethod error");
					}

					inputcloud.generateFuzzyCloudFunction();

					cout <<"\n"<< inputcloud.dataVec.size();
					////inputcloud.Print();
					CutPipeCloud pipcloud(inputcloud);
					pipcloud.endFunction = [&]() {
						 cout << "\n======PipeEnd======";
							for (auto& pipeiter : pipcloud.pipeVec) {
								Vec4* ori = (Vec4*)pipeiter->nodeVec.back()->outputDataVec[0].data;
								Vec4 temcpos = Vec4((int)ori->x, (int)ori->y, (int)ori->z);
							Vec4* temrot = (Vec4*)pipeiter->nodeVec[0]->inputDataVec[1].data;
								CutOutPutData tem = CutOutPutData(temcpos, *temrot);
								if (std::find(pipcloud.outputCloud.dataVec.begin(), pipcloud.outputCloud.dataVec.end(), tem) == pipcloud.outputCloud.dataVec.end()) {
									pipcloud.outputCloud.dataVec.push_back(tem);
								}
							}
							//改动部分
							//pipcloud.outputCloud.TransToWorldCoo1( EQS.GetTargetPos(tparams["target"][Jint(i)].asInt()), EQS.GetTargetRot(tparams["target"][Jint(i)].asInt()));
							pipcloud.outputCloud.TransToWorldCoo(EQS.GetTargetCoordinate(tparams["target"][Jint(i)].asInt()));
							pipcloud.outputCloud.SetRateAndToFile("D:\\VCP2\\VCP2outTest_"+numToString<int>(i)+".txt");

					};
					pipcloud.PumpStart();
				}
				//???
				//下面得所有pipecloud结束后才能调用，不能像现在直接顺序调用
				string afterInterFilePath;
				if (targetNum == 1) {
					//只有一个，不用求交
					afterInterFilePath = "D:\\VCP2\\VCP2outTest_0.txt";
				}
				else {
					//???
					//求交先只实现2个的
					CutCloudSet set1,set2;
					set1.InitByFile("D:\\VCP2\\VCP2outTest_0.txt");
					set2.InitByFile("D:\\VCP2\\VCP2outTest_1.txt");
					set1.IntersectionAndToFile(set2,"D:\\VCP2\\VCP2interTest.txt");

					afterInterFilePath = "D:\\VCP2\\VCP2interTest.txt";
				}

				//从模糊点云中选取最佳点
				int selectMethod = tshot["selectMethod"].asInt();
				cout << "\nselectMethod:" << selectMethod;

				CutOutPutData finalPoint;
				if (selectMethod == 0) {
					//随机,从afterInterFile中随机选取一组pos,rot
					CutCloudSet tset;
					tset.InitVecByFile(afterInterFilePath);
					std::random_device rd;
					std::default_random_engine e(rd());
					std::uniform_int_distribution<> u(0, tset.outVec.size()-1);
					finalPoint=tset.outVec[u(e)];
				}
				else {
					throw VCPError("SelectMethod Error in parsing ShotScript");
				}
				/*finalPoint.centerCPos.Print();
				finalPoint.rot.Print();*/

				//根据id,duration,fps,finalPoint生成最终序列帧
				for (int tf = startFrameID; tf <= endFrameID; tf++) {
					ofile << numToString<int>(tf) << " " << numToString<int>(finalPoint.centerCPos.x) << " " << numToString<int>(finalPoint.centerCPos.y) << " " << numToString<int>(finalPoint.centerCPos.z) << \
						" " << numToString<int>(finalPoint.rot.x) << " " << numToString<int>(finalPoint.rot.y) << " " << numToString<int>(finalPoint.rot.z)<<"\n";
				}
			}//Cut
			else if (type == 1) {
				//Surround
				//???
				//json中有把target改成多个的可能
				cout << "\n########################################################";
				cout << "\nSurround";
				float x = tparams["localOffset"][Jint(0)][Jint(0)].asDouble();
#define JGet(name,index) tparams[name][Jint(0)][Jint(index)].asDouble()
#define JVec2(name) Vec2(JGet(name,0),JGet(name,1))
#define JVec4(name) Vec4(JGet(name,0),JGet(name,1),JGet(name,2))
				CutInputData surroundInput(JVec4("localOffset"), JVec4("rot"),JVec2("s1"), JVec2("s2"));
				CutInputCloud inputcloud(surroundInput);
				
				if (fuzzyMethod == 0) {
					inputcloud.generateFuzzyCloudFunction = [&]() {
#define JFGet(name,index) tfparams[name][Jint(index)].asDouble()
#define JFVec4(name) Vec4(JFGet(name,0),JFGet(name,1),JFGet(name,2))
						for (Vec4 rot = inputcloud.baseData.rot; rot < JFVec4("unreachedMaxRot"); rot += JFVec4("deltaRot")) {
							inputcloud.dataVec.push_back(CutInputData(inputcloud.baseData.localOffset, rot, inputcloud.baseData.s1, inputcloud.baseData.s2));
							inputcloud.rateVec.push_back(1.0f);
						}
					};
				}
				else {
					throw VCPError("FuzzyMethod error");
				}
				inputcloud.generateFuzzyCloudFunction();

				string finalFilePath = "D:\\VCP2\\VCP2outTest_surround.txt";
				CutPipeCloud pipcloud(inputcloud);
				pipcloud.endFunction = [&]() {
					cout << "\n======PipeEnd======";
					for (auto& pipeiter : pipcloud.pipeVec) {
						Vec4* ori = (Vec4*)pipeiter->nodeVec.back()->outputDataVec[0].data;
						Vec4 temcpos = Vec4((int)ori->x, (int)ori->y, (int)ori->z);
						Vec4* temrot = (Vec4*)pipeiter->nodeVec[0]->inputDataVec[1].data;
						CutOutPutData tem = CutOutPutData(temcpos, *temrot);
						if (std::find(pipcloud.outputCloud.dataVec.begin(), pipcloud.outputCloud.dataVec.end(), tem) == pipcloud.outputCloud.dataVec.end()) {
							pipcloud.outputCloud.dataVec.push_back(tem);
						}
					}
					//改动部分
					//???
					//以后多target
					pipcloud.outputCloud.TransToWorldCoo(EQS.GetTargetCoordinate(tparams["target"][Jint(0)].asInt()));
					pipcloud.outputCloud.SetRateAndToFile(finalFilePath);
				};
				pipcloud.PumpStart();

				//???
				//下面得pipecloud结束后才能调用，不能像现在直接顺序调用

				//根据id,duration,fps,outFile生成最终序列帧
				//???
				//这里默认了duration*fps==tset.vec.size()
				CutCloudSet tset;
				tset.InitVecByFile(finalFilePath);

				for (int tf = startFrameID; tf <= endFrameID; tf++) {
					CutOutPutData tdata = tset.outVec[tf - startFrameID];
					ofile << numToString<int>(tf) << " " << numToString<int>(tdata.centerCPos.x) << " " << numToString<int>(tdata.centerCPos.y) << " " << numToString<int>(tdata.centerCPos.z) << \
						" " << numToString<int>(tdata.rot.x) << " " << numToString<int>(tdata.rot.y) << " " << numToString<int>(tdata.rot.z) << "\n";
				}
				
			}
			else if (type == 2) {
				cout << "\n########################################################";
				cout << "\nStaticFollow";
				//???
				//json中有把target改成多个的可能
				int targetID = tparams["target"][Jint(0)].asInt();
#define JGet(name,index) tparams[name][Jint(0)][Jint(index)].asDouble()
#define JVec2(name) Vec2(JGet(name,0),JGet(name,1))
#define JVec4(name) Vec4(JGet(name,0),JGet(name,1),JGet(name,2))
				Vec4 cameraWP=JVec4("staticCameraWP");
				CutInputCloud inputcloud;
				if (fuzzyMethod == 0) {
					inputcloud.generateFuzzyCloudFunction = [&]() {
						for (int i = startFrameID; i <= endFrameID; i++) {
							//???
							//有问题
							//rot
							Vec4 temCpos = cameraWP-EQS.GetTargetPos(targetID,i);//???
							Vec4 temRot = Vec4(0, 0, -ArcToDegree(atan2(temCpos.x, temCpos.y)));
							//temRot.Print();
							//s1
							Vec2 s1 = JVec2("s1");
							//s2
							Vec2 s2= GetScreenPos(CameraIns::TemCamera(), temCpos + JVec4("localOffset"));
							inputcloud.dataVec.push_back(CutInputData(JVec4("localOffset"),temRot,s1,s2));
							inputcloud.rateVec.push_back(1.0f);
						}
					};
				}
				else {
					throw VCPError("FuzzyMethod error");
				}
				inputcloud.generateFuzzyCloudFunction();
				/////////////////////////
				string finalFilePath = "D:\\VCP2\\VCP2outTest_staticFollow.txt";
				CutPipeCloud pipcloud(inputcloud);
				pipcloud.endFunction = [&]() {
					cout << "\n======PipeEnd======";
					for (auto& pipeiter : pipcloud.pipeVec) {
						Vec4* ori = (Vec4*)pipeiter->nodeVec.back()->outputDataVec[0].data;
						Vec4 temcpos = Vec4((int)ori->x, (int)ori->y, (int)ori->z);
						Vec4* temrot = (Vec4*)pipeiter->nodeVec[0]->inputDataVec[1].data;
						CutOutPutData tem = CutOutPutData(temcpos, *temrot);
						if (std::find(pipcloud.outputCloud.dataVec.begin(), pipcloud.outputCloud.dataVec.end(), tem) == pipcloud.outputCloud.dataVec.end()) {
							pipcloud.outputCloud.dataVec.push_back(tem);
						}
					}
					//改动部分
					//???
					pipcloud.outputCloud.TransToWorldCoo3();
					pipcloud.outputCloud.SetRateAndToFile(finalFilePath);
				};
				pipcloud.PumpStart();

				//???
				//下面得pipecloud结束后才能调用，不能像现在直接顺序调用

				//根据id,duration,fps,outFile生成最终序列帧
				//???
				//这里默认了duration*fps==tset.vec.size()
				CutCloudSet tset;
				/*tset.InitVecByFile(finalFilePath);

				for (int tf = startFrameID; tf <= endFrameID; tf++) {
					CutOutPutData tdata = tset.outVec[tf - startFrameID];
					ofile << numToString<int>(tf) << " " << numToString<int>(tdata.centerCPos.x) << " " << numToString<int>(tdata.centerCPos.y) << " " << numToString<int>(tdata.centerCPos.z) << \
						" " << numToString<int>(tdata.rot.x) << " " << numToString<int>(tdata.rot.y) << " " << numToString<int>(tdata.rot.z) << "\n";
				}
				*/
				
			}
			else {
				throw VCPError("Shot type error in parsing ShotScript,type" + type);
			}
		}//for:tshot

		ofile.close();
	}

}
