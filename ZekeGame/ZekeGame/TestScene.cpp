#include "stdafx.h"
#include <fstream>
#include "GameCamera.h"
#include "Game/GameCamera2D.h"
#include "Game/GameCursor.h"
#include "TestScene.h"
#include "TestScene2.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	delete m_camera;
	DeleteGO(m_2dcamera);
	DeleteGO(m_boneModel);
}


bool TestScene::Start() {
	m_camera = new GameCamera;
	m_2dcamera = new GameCamera2D;
	m_camera->SetTarget(CVector3::Zero());
	CVector3 ppp = CVector3::Zero();
	ppp.z -= 3.f;
	m_camera->SetPosition(ppp);
	m_camera->Update();
	{
		using namespace std;
		ofstream fout;
		double a;
		fout.open("datafile.txt", ios::out | ios::binary | ios::trunc);
		a = 0;
		fout.write((char*)&a, sizeof(double));
		fout.close();
	}
	{
		using namespace std;
		char outfile[] = "datafile.txt";  

		ifstream fin(outfile, ios::in | ios::binary);
		if (!fin) {
			OutputDebugStringA("datafileのオープンに失敗しました");
			return 1;
		}
		double d;  

		fin.read((char *)&d, sizeof(double));
		char message[256];
		sprintf_s(message,"%f\n",d);
		OutputDebugStringA(message);
		fin.close();  
	}
	m_boneModel = NewGO<SkinModelRender>(0, "model");
	m_anim[0].Load(L"Assets/modelData/uma/anim_uma_atack.tka");
	m_anim[0].SetLoopFlag(true);
	m_boneModel->Init(L"Assets/modelData/uma.cmo",m_anim,1,enFbxUpAxisZ,"PSMain","VSMainSkin");
	m_boneModel->SetPosition(CVector3::Zero());
	m_boneModel->PlayAnimation(0);
	m_sp = NewGO<SpriteRender>(0);
	m_sp->Init(L"Assets/Sprite/leftButton.dds", 50.f, 50.f);
	m_sp->SetPosition(pos);
	return true;
}


void TestScene::Update() {
	if (Mouse::isTrigger(enRightClick)) {
		pos = CVector3::Zero();
	}
	m_camera->Update();
	char str[256];
	double num = 0,f;
	static double t = 0.f;
	static bool add = false;
	if (Mouse::isTrigger(enLeftClick)) {
		add = true;
	}
	//if (t >= 1.f) {
	//	t = 0.0f;
	//	add = false;
	//}
	if (add) {
		t += 0.1;
	}
	static double time = 0;
	if (time >= 2.f) {
		time = 0.f;
		add = false;
	}
	if (add) {
		time += 0.1f;
	}
	num = EASE::InOutQuad(50.f,0.f,1.f,time);
	sprintf_s(str, "%f\n", num);
	OutputDebugStringA(str);
	pos.x += num;
	m_sp->SetPosition(pos);
}

void TestScene::PostRender() {
}