#include <iostream>
#include "Math.h"
#include "ShootTarget.h"
#include "Camera.h"
#include "TransFunction.h"
#include "Cut.h"
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

	Vec4 M_vec(0, 0, 40), rot(0, 0, 0);
	Vec2 s1(0.0f, -0.8f), s2(0.0f, 0.8f);
	/*
	Vec4 dvec = GetRotated(M_vec, rot);
	//dvec.Print();
	Vec2 t1t2 = GetT1T2(dvec, s1, s2, CameraIns::TemCamera());
	Vec4 C_vec = GetCPosBySpos(s1, CameraIns::TemCamera(), t1t2.x);
	C_vec.Print();
	*/
	//////
	
	CutInputData input(M_vec,rot,s1,s2);

	
	//CutPipe pipe;
	//pipe.InitInput(input);
	//pipe.Assemble();
	//pipe.PumpStart();
	//pipe.PrintOutput();
	
	
	CutInputCloud inputcloud(input);
	inputcloud.GenerateFuzzyCloud();
	cout <<"\n"<< inputcloud.dataVec.size();
	//inputcloud.Print();
	CutPipeCloud pipcloud(inputcloud);
	//cout << "\ncloud init end.";
	pipcloud.PumpStart();
	

	system("pause");
    return 0;
}

