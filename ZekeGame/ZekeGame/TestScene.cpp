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
	m_model = NewGO<SkinModelRender>(0);
	m_model->Init(L"Assets/modelData/uma.cmo");
	m_model->SetPosition({ 0,0,130 });
	
	m_spp = NewGO<SpriteRender>(0);
	m_spp->Init(L"Assets/sprite/hakkou1.dds", 1280, 720);
	m_spp->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Perspective);
	m_spp->SetPosition({ 30,0,900 });
	
	//	m_efk = NewGO<CEffect>(0, "DRB");
	//m_efk->SetScale({ 15.f,15.f,15.f });
	////m_efk->SetScale({ 13.f,13.f,13.f });
	//m_efk->SetPosition({ 0.f,0.f,550.f });
	//auto pp = m_model->GetPosition();
	//m_efk->Play(L"Assets/effect/drback.efk");
	//
	m_sp = NewGO<SpriteRender>(0);
	m_sp->Init(L"Assets/sprite/wallpaper2.dds", 1280, 720);
	m_sp->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Perspective);
	m_sp->SetPosition({ 30,0,800 });


	m_efk = NewGO<CEffect>(0, "DRB");
	m_efk->SetScale({ 15.f,15.f,15.f });
	//m_efk->SetScale({ 13.f,13.f,13.f });
	m_efk->SetPosition({ 0.f,0.f,330.f });
	auto pp = m_model->GetPosition();
	m_efk->Play(L"Assets/effect/drback.efk");
	return true;
}

void TestScene::OnDestroy() {
	DeleteGO(m_sp);
	DeleteGO(m_efk);
	//DeleteGO(m_model);
}


void TestScene::Update() {
	if (Mouse::isPress(enLeftClick)) {
		//auto p = m_efk->GetPosition();
		//p.z += 10.f;
		//m_efk->SetPosition(p);

		auto p = m_sp->GetPosition();
		p.z += 10.f;
		m_sp->SetPosition(p);
	}
	if (Mouse::isPress(enRightClick)) {
		//auto p = m_efk->GetPosition();
		//p.z -= 10.f;
		//m_efk->SetPosition(p);

		auto p = m_sp->GetPosition();
		p.z -= 10.f;
		m_sp->SetPosition(p);
	}
}
