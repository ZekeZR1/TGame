#include "stdafx.h"
#include <fstream>
#include "GameCamera.h"
#include "Game/GameData.h"
#include "Game/Dungeon/DungeonData.h"
#include "Game/GameCamera2D.h"
#include "Game/GameCursor.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "Engine\sound\CSound.h"
#include"Engine/physics/PhysicsStaticObject.h"
#include"Engine/character/CharacterController.h"
#include "Game/MonsterBox/MonsterBox.h"

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	DeleteGO(m_model);
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
	g_graphicsEngine->SetAmbientLight(1.f);
	m_model = NewGO<SkinModelRender>(0);
	m_model->Init(L"Assets/modelData/Test.cmo", nullptr, 0, enFbxUpAxisZ, "PSMain", "VSMain",nullptr , L"spectest.jpg");
	CVector3 moveSpeed;

	pos + moveSpeed * IGameTime().GetFrameDeltaTime();
	m_model->SetPosition(pos);
	return true;
}


void TestScene::Update() {
	camera2d->Update();
	camera3d->Update();
	static CVector3 pos = CVector3::Zero();
	const float movesp = 30.f;
	if (g_pad[0].IsPress(enButtonDown)) {
		pos.z -= movesp;
	}
	if (g_pad[0].IsPress(enButtonLeft)) {
		pos.x += movesp;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		IMonsterBox().WriteFile(0);
		pos.x -= movesp;
	}
	if (g_pad[0].IsTrigger(enButtonA)) {
		IMonsterBox().GetMonster(enUmataur);
		OutputDebugStringA("I Got a Uma!!\n");
		pos.y += movesp;
	}
	if (g_pad[0].IsPress(enButtonB)) {
		IMonsterBox().GetMonster(enFairy);
		OutputDebugStringA("I Got a Fairy!!\n");
		pos.y -= movesp;
	}
	if (g_pad[0].IsPress(enButtonX)) {
		if (IMonsterBox().isGot(enUmataur)) {
			OutputDebugStringA("I have a Uma!!\n");
		}
		else {
			OutputDebugStringA("I dont have a Uma!!\n");
		}
		pos.z += movesp;
	}
	if (g_pad[0].IsPress(enButtonY)) {
		if (IMonsterBox().isGot(enFairy)) {
			OutputDebugStringA("I have a enFairy!!\n");
		}
		else {
			OutputDebugStringA("I dont have a enFairy!!\n");
		}
		pos.z += movesp;
	}
	float rx = g_pad[0].GetRStickXF();
	CQuaternion rott = CQuaternion::Identity();
	rott.SetRotationDeg(CVector3::AxisY(), rx * 2.f);
	m_rot.Multiply(rott);
	m_model->SetRotation(m_rot);
	m_model->SetPosition(pos);
}
