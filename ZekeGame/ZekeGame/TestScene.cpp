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
	cur = NewGO<GameCursor>(0);

	sp = NewGO<SpriteRender>(0);
	sp->Init(L"Assets/sprite/leftButton.dds",300,50,true,true);
	sp->SetPosition({ 0,0,0 });
	//sp->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Perspective);

	//spp = NewGO<SpriteRender>(0);
	//spp->Init(L"Assets/sprite/rightButton.dds", 50, 300, true, true);
	//spp->SetPosition({ 0,0,0 });
	//spp->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Perspective);

	efk = NewGO<CEffect>(0);
	efk->Play(L"Assets/effect/majinken_wiat.efk");
	return true;
}

void TestScene::OnDestroy() {
}


void TestScene::Update() {
	auto p = cur->GetCursor();
	sp->SetCollisionTarget(p);
	/*spp->SetCollisionTarget(p);*/
}
