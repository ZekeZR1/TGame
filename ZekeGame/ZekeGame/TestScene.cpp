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
			OutputDebugStringA("datafile‚ÌƒI[ƒvƒ“‚É¸”s‚µ‚Ü‚µ‚½");
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
	return true;
}


void TestScene::Update() {
	m_camera->Update();
}

void TestScene::PostRender() {
}