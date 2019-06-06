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

//TODO : alpha, shadow
bool TestScene::Start() {
	//m_model = NewGO<SkinModelRender>(0);
	//m_model->Init(L"Assets/modelData/uma.cmo");
	//m_model->SetPosition({ 0,0,130 });
	m_cur = NewGO<GameCursor>(0);

	m_sp = NewGO<SpriteRender>(0);
	m_sp->Init(L"Assets/sprite/hakkou1.dds", 300, 300,true,true);

	m_spp = NewGO<SpriteRender>(0);
	m_spp->Init(L"Assets/sprite/hakkou1.dds", 200, 500, true, true);
	//m_sp->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Perspective);
	//m_sp->SetPosition({ 30,0,900 });
	
	//m_efk = NewGO<CEffect>(0, "DRB");
	//m_efk->SetScale({ 15.f,15.f,15.f });
	////m_efk->SetScale({ 13.f,13.f,13.f });
	//m_efk->SetPosition({ 0.f,0.f,330.f });
	//auto pp = m_model->GetPosition();
	//m_efk->Play(L"Assets/effect/drback.efk");
	return true;
}

void TestScene::OnDestroy() {
	DeleteGO(m_sp);
	DeleteGO(m_cur);
}


void TestScene::Update() {
	m_sp->SetCollisionTarget(m_cur->GetCursor());
	m_spp->SetCollisionTarget(m_cur->GetCursor());
}
