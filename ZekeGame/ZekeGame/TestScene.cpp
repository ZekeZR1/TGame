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
		auto efk = NewGO<CEffect>(0);
		efk->Play(L"Assets/effect/majinken_attack.efk");
	}
}
