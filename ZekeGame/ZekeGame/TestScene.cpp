#include "stdafx.h"
#include <fstream>
#include "GameCamera.h"
#include "Game/Dungeon/DungeonData.h"
#include "Game/GameCamera2D.h"
#include "Game/GameCursor.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "Engine\sound\CSound.h"
#include"Engine/physics/PhysicsStaticObject.h"
#include"Engine/character/CharacterController.h"

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	DeleteGO(m_white);
	DeleteGO(m_model);
	DeleteGO(m_mo2);
	//DeleteGO(m_sp);
}

//TODO : alpha, shadow
bool TestScene::Start() {
	{
		//g_physics.GetDynamicWorld()->getDebugDrawer()->setDebugMode(1);
		g_physics.SetDebugDraw(true);
		camera2d = new Camera;
		camera2d->SetTarget(CVector3::Zero());
		camera2d->SetPosition({ 0.0f, 0.0f, -10.0f });
		camera2d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
		camera2d->SetNear(0.1f);
		camera2d->SetFar(1000.0f);
		camera2d->Update();
		CVector3 ppp = CVector3::Zero();
		ppp.z = 500.f;
		ppp.y += 200.f;
		camera3d = new Camera;
		camera3d->SetTarget(CVector3::Zero());
		camera3d->SetPosition(ppp);
		camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
		camera3d->SetNear(0.1f);
		camera3d->SetFar(50000.0f);
		camera3d->Update();
	}
	m_model = NewGO<SkinModelRender>(0, "model");
	m_anim[0].Load(L"Assets/modelData/uma/anim_uma_walk.tka");
	m_anim[0].SetLoopFlag(true);
	m_model->Init(L"Assets/modelData/uma.cmo",m_anim,1);
	m_model->PlayAnimation(0);
	m_model->SetShadowReciever(false);
	m_charaCon.Init(30,20,CVector3::Zero(),enFbxUpAxisY);
	m_mo2 = NewGO<SkinModelRender>(0);
	m_mo2->Init(L"Assets/modelData/uma.cmo");
	m_mo2->SetPosition(pos2);
	m_charaCon2.Init(30, 50, pos2, enFbxUpAxisY);
	//IGameObjectManager().AddShadowCaster(&(m_model->GetSkinModel()));
	m_back = NewGO<SkinModelRender>(0);
	m_back->Init(L"Assets/modelData/dun.cmo");
	m_phy.CreateMeshObject(m_back->GetSkinModel(), CVector3::Zero(), CQuaternion::Identity());

	g_graphicsEngine->SetAmbientLight(1.f);

	m_white = NewGO<SpriteRender>(0);
	m_white->Init(L"Assets/Sprite/DadanDanBk.dds", 500.f, 500.f);
	m_white->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Ortho);
	//m_white->SetMulCol({ 0.f,1.f,0.f,1.f });
	//

	//IDungeonData().SetDunNum(12);

	//int num = IDungeonData().GetDungeonNum();
	//char str[256];
	//sprintf_s(str, "%d\n", num);
	//OutputDebugStringA(str);
	return true;
}


void TestScene::Update() {
	camera2d->Update();
	camera3d->Update();
	static CVector3 p = CVector3::Zero();
	//if (g_pad[0].IsTrigger(enButtonA)) {
		//	auto s = NewGO<Sound>(0);
	//		s->Init(L"Assets/sound/coinGet.wav");
			//s->Play();
		//	p.z += 10.f;
		//}
		//if (g_pad[0].IsPress(enButtonB)) {
		//	p.z -= 10.f;
		//}
	CVector3 moveSpeed = CVector3::Zero();
	if (g_pad[0].IsPress(enButtonUp)) {
		moveSpeed.z = 1000.f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		moveSpeed.z = -1000.f;
	}
	if (g_pad[0].IsPress(enButtonLeft)) {
		moveSpeed.x = 500.f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		moveSpeed.x = -500.f;
	}
	//CVector3 pos = m_charaCon.Execute(IGameTime().GetFrameDeltaTime(), moveSpeed);
	m_model->SetPosition(m_charaCon.Execute(IGameTime().GetFrameDeltaTime(), moveSpeed));

	static float alpha = 0.f;
	if (Mouse::isTrigger(enNotchUp)) {
		alpha += 0.1f;
	}
	if (Mouse::isTrigger(enNotchDown)) {
		alpha -= 0.1f;
	}
	m_white->SetMulCol({ 0.f,1.f,0.f,alpha });
	char str[256];
	sprintf_s(str, "alpha..%f\n", alpha);
	OutputDebugStringA(str);
}
