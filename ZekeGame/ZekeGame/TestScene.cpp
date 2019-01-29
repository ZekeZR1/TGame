#include "stdafx.h"
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