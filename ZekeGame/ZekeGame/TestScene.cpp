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
	m_meModel->SetPosition(m_mePos);
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
	{
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
	}

	m_anotherMonster->SetPosition(p);
	//auto toTarV =;
	//auto toAnotherV = m_anotherMonster->GetPosition() - m_meModel->GetPosition();
	float laserRange = 100;
	auto crs = m_targetModel->GetPosition() - m_meModel->GetPosition();
	crs.Cross(CVector3::Up());
	crs.Normalize();
	crs *= laserRange;
	CLOCKWISE LeftResult, RightResult;

	//左端より右か
	{
		auto LeftMyPos = m_meModel->GetPosition() + crs;
		auto LeftTarPos = m_targetModel->GetPosition() + crs;
		auto leftV = LeftTarPos - LeftMyPos;
		auto toAnotherVfromLeft = m_anotherMonster->GetPosition() - LeftMyPos;
		LeftResult = CVector3::ccw(leftV, toAnotherVfromLeft);
	}
	//右端より左か
	{
		auto RightMyPos = m_meModel->GetPosition() - crs;
		auto RightTarPos = m_targetModel->GetPosition() - crs;
		auto rightV = RightTarPos - RightMyPos;
		auto toAnotherVfromRight = m_anotherMonster->GetPosition() - RightMyPos;
		RightResult = CVector3::ccw(rightV, toAnotherVfromRight);
	}
	//技を撃ってるモンスターより前側か
	bool isFront = true;
	{
		auto v1 = m_targetModel->GetPosition() - m_meModel->GetPosition();
		auto v2 = m_anotherMonster->GetPosition() - m_meModel->GetPosition();
		if (v1.Dot(v2) < 0) {
			isFront = false;
		}
		/*auto toAnotherVfromMe = m_anotherMonster->GetPosition() - RightMyPos;
		RightResult = CVector3::ccw(crs, toAnotherVfromMe);*/
	}
	//if (LeftResult == enCLOCKWISE and RightResult == enCOUNTER_CLOCKWISE and isFront) {
	//	OutputDebugString("HITTING\n");
	//}
	//else {
	//	OutputDebugString("\n");
	//}
	//
	//auto result = CVector3::ccw(toTarV, toAnotherV);
	//m_anotherMonster->SetPosition(tarpos);
	/*switch (leftResult) {
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
	}*/
}
