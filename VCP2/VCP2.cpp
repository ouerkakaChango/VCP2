#include <iostream>
#include "ShotScript.h"
#include "EnvironmentQuerySystem.h"
#include "TransFunction.h"
using namespace VCP;
using std::cout;
int main()
{
	/*
	ShootTarget target1(100.0f, 100.0f, 50.0f);
	Vec2 screenpos = GetScreenPos(camera, Vec4(target1.x,target1.y,target1.z));
	cout << "\n"<<screenpos.x << " " << screenpos.y;
	cout << "\n" << (screenpos.x+1.0f)*1920.0f/2.0f << " " << (screenpos.y+1.0f)*1080.0f/2.0f;

	Vec4 temtargetpos = GetCPosBySpos(0.5, -0.5, camera, 20.0f);
	temtargetpos.Print();
	*/
	/*
	Vec4 M_vec(0,0,100);
	Vec4 dvec=GetRotated(M_vec, 0, 0, -180.0f);
	Vec2 t1t2 = GetT1T2(dvec,Vec2(0,0), Vec2(0,0.5), camera);
	
	Vec4 C_vec = GetCPosBySpos(0, 0, camera, t1t2.x);
	C_vec.Print();
	*/

	/*
	Vec4 dvec = GetRotated(M_vec, rot);
	//dvec.Print();
	Vec2 t1t2 = GetT1T2(dvec, s1, s2, CameraIns::TemCamera());
	Vec4 C_vec = GetCPosBySpos(s1, CameraIns::TemCamera(), t1t2.x);
	C_vec.Print();
	*/

	//CutPipe pipe;
	//pipe.InitInput(input);
	//pipe.Assemble();
	//pipe.PumpStart();
	//pipe.PrintOutput();

	////////////////////////

	//Vec4 M_vec(0, 0, 180), rot(0, 0, 0);
	//Vec2 s1(0.0f, -0.5f), s2(0.0f, 0.5f);
	//CutInputData input(M_vec,rot,s1,s2);
	//
	//
	//CutInputCloud inputcloud(input);
	//inputcloud.GenerateFuzzyCloud();
	//cout <<"\n"<< inputcloud.dataVec.size();
	////inputcloud.Print();
	//CutPipeCloud pipcloud(inputcloud);
	//pipcloud.PumpStart();
	
	///
	/*Vec4 M_vec2(0, 0, 180), rot2(0, 0, 45.0f);
	Vec2 s12(0.5f, -0.5f), s22(0.5f, 0.5f);
	CutInputData input2(M_vec2, rot2, s12, s22);
	CutInputCloud inputcloud2(input2);
	inputcloud2.GenerateFuzzyCloud();
	cout << "\n" << inputcloud2.dataVec.size();
	CutPipeCloud pipcloud2(inputcloud2);
	pipcloud2.PumpStart();*/

	
	//Çó½»
	/*CutCloudSet set1,set2;
	set1.InitByFile("D:\\VCP2.txt");
	set2.InitByFile("D:\\VCP2_2.txt");
	set1.IntersectionAndToFile(set2,"D:\\Inter.txt");*/

	//»·ÅÄ
	/*Vec4 M_vec3(0, 0, 180), rot3(0, 0, 0.0f);
	Vec2 s13(0.0f, -0.5f), s23(0.0f, 0.5f);
	CutInputData input3(M_vec3, rot3, s13,s23);
	CutInputCloud inputcloud3(input3);
	inputcloud3.GenerateSurroundCloud();
	cout << "\n" << inputcloud3.dataVec.size();
	CutPipeCloud pipcloud3(inputcloud3);
	pipcloud3.PumpStart();*/

	/////////////////////////////////////////////////////////////////////////
	if (EQS.Init("D:\\VCP2\\storyScript1.txt")) {
		ShotScript script("D:\\VCP2\\script2.txt");
	}
	else {
		abort();
	}
	////////////////////////////////////////////////////////////////////////
	/*auto s2 = GetScreenPos(CameraIns::TemCamera(), Vec4(320,0,-90)+Vec4(0,0,180));
	s2.Print();
	Vec4 dvec = GetRotated(Vec4(0, 0, 180), Vec4(0, 0, -63.435f));
	Vec2 t1t2 = GetT1T2(dvec, Vec2(0, -0.5), Vec2(0, 0), CameraIns::TemCamera());
	Vec4 C_vec = GetCPosBySpos(Vec2(0, -0.5), CameraIns::TemCamera(), t1t2.x);
	C_vec.Print();*/
	/////////////////////////////////////////////////////////////////////////
	//Coordinate3 worldCoo(Vec4(0, 0, 0), Vec4(1, 0, 0), Vec4(0, 1, 0), Vec4(0, 0, 1));
	////Coordinate3 ObjCoo(Vec4(1000, 0, 0), Vec4(-sqrt(3.0f) / 2.0f, 0, -1 / 2.0f), Vec4(0, -1, 0), Vec4(-1 / 2.0f, 0, sqrt(3.0f) / 2.0f));
	//Coordinate3 ObjCoo(Vec4(1000, 0, 0), Vec4(-1,0,0), Vec4(0, -1, 0), Vec4(0,0,1));
	//Coordinate3 cameraCooInObjCoo = RevertInfo(ObjCoo, Vec4(200, 50, -100), Vec4(0, 0, 0));
	//Vec4 WP= CooTrans(worldCoo, ObjCoo, cameraCooInObjCoo.origin);
	//WP.Print();
	//Vec4 WR = GetWR(worldCoo, ObjCoo, cameraCooInObjCoo);
	//WR.Print();
	////////////////////////////////////////////////////////////////////////
	system("pause");
    return 0;
}

