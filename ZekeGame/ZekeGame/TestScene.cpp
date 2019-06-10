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
	m_meModel = NewGO<SkinModelRender>(0);
	m_meModel->Init(L"Assets/modelData/uma.cmo");
	m_targetModel = NewGO<SkinModelRender>(0);
	m_targetModel->Init(L"Assets/modelData/uma.cmo");
	m_targetModel->SetPosition(m_targetPos);
	m_anotherMonster = NewGO<SkinModelRender>(0);
	m_anotherMonster->Init(L"Assets/modelData/uma.cmo");
	return true;
}

void TestScene::OnDestroy() {
}


void TestScene::Update() {
	auto p = m_anotherMonster->GetPosition();
	double movs = 10;
	if (g_pad[0].IsPress(enButtonUp)) {
		p.z += movs;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		p.z -= movs;
	}
	if (g_pad[0].IsPress(enButtonLeft)) {
		p.x -= movs;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		p.x += movs;
	}
	m_anotherMonster->SetPosition(p);
	auto toTarV = m_targetModel->GetPosition() - m_meModel->GetPosition();
	auto toAnotherV = m_anotherMonster->GetPosition() - m_meModel->GetPosition();
	auto result = ccw(toTarV, toAnotherV);
	switch (result) {
	case enCOUNTER_CLOCKWISE:
		OutputDebugString("enCOUNTER_CLOCKWISE\n");
			break;
	case enCLOCKWISE:
		OutputDebugString("enCLOCKWISE\n");
			break;
	case enONLINE_BACK:
		OutputDebugString("enONLINE_BACK\n");
			break;
	case enONLINE_FRONT:
		OutputDebugString("enONLINE_FRONT\n");
			break;
	case enON_SEGMENT:
		OutputDebugString("enON_SEGMENT\n");
			break;
	}
}
