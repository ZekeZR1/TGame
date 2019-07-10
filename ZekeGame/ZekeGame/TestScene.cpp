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
#include "Game/Monster/Monsters/Book.h"

//TODO : alpha, shadow
bool TestScene::Start() {

	camera3d->SetTarget(CVector3::Zero());
	camerapos = { 200,150,-400 };
	camera3d->SetPosition(camerapos);
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->SetNear(0.1f);
	camera3d->SetFar(50000.0f);
	camera3d->Update();

	m_model = NewGO<SkinModelRender>(0, "model");
	m_model->SetShadowCasterFlag(false);
	m_model->Init(L"Assets/modelData/dun.cmo", nullptr, 0, enFbxUpAxisZ, "PSMainStage");
	m_model->SetPosition(CVector3::Zero());

	m_floor = NewGO<SkinModelRender>(0, "model");
	m_floor->Init(L"Assets/modelData/dun_yuka.cmo");
	m_floor->SetPosition(CVector3::Zero());

	m_monster = NewGO<SkinModelRender>(0);
	m_monster->Init(L"Assets/modelData/book.cmo");

	m_anim[Monster::en_idle].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);

	m_anim[Monster::en_atack].Load(L"Assets/modelData/book/book_attack.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);

	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(true);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/book/book_idle.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(true);

	m_monster->Init(L"Assets/modelData/book.cmo", m_anim, 6);
	m_monster->PlayAnimation(0);


	auto mon1 = NewGO<SkinModelRender>(0);
	mon1->Init(L"Assets/modelData/hero.cmo",nullptr,0,enFbxUpAxisY);
	mon1->SetPosition({ 300,0,0 });

	return true;
}

void TestScene::OnDestroy() {
	DeleteGO(m_model);
	DeleteGO(m_floor);
}


void TestScene::Update() {
	/*if (g_pad[0].IsPress(enButtonA)) {
		camerapos.x += 100;
	}
	if (g_pad[0].IsPress(enButtonB)) {
		camerapos.x -= 100;
	}

	if (g_pad[0].IsPress(enButtonLeft)) {
		camerapos.z += 100;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		camerapos.z -= 100;
	}

	if (g_pad[0].IsPress(enButtonUp)) {
		camerapos.y += 100;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		camerapos.y -= 100;
	}*/
	camera3d->SetPosition(camerapos);
	camera3d->Update();
}
