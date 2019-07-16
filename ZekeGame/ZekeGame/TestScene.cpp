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
	return true;
}

void TestScene::OnDestroy() {
}


void TestScene::Update() {

	if (g_pad[0].IsTrigger(enButtonA)) {
		m_se = NewGO<Sound>(0);
		m_se->Init(L"Assets/sound/blizzard.wav");
		vol = 1.f;
		m_se->Play();
	}

	if (g_pad[0].IsTrigger(enButtonB)) {
		m_se->Stop();
	}

	if (m_se == nullptr or m_se->IsDead()) return;
	m_se->SetVolume(vol);
	if (vol >= 0)
		vol -= 0.01;
	if (m_se->isPlaying())
		OutputDebugString("PLAYING\n");
	else
		OutputDebugString("STOPPING\n");
}
