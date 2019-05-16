#include "stdafx.h"
#include "Game.h"
#include "GameCamera3D.h"
#include "GameCamera2D.h"
#include "Title/ModeSelect.h"
#include "Fade/Fade.h"

#include "../TestScene.h"
#include "../Game/Dungeon/MonsterDrop.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	//Initialize
	Engine::IEngine().Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	NewGO<Fade>(0, "fade");
	NewGO<GameCamera3D>(0, "cam3d");
	NewGO<GameCamera2D>(0, "cam2d");
	NewGO<ModeSelect>(0, "modesel");
	//NewGO<MonsterDrop>(0);
	g_physics.SetDebugDraw(true);

	/*AnimationClip anim[3];
	anim[0].Load(L"Assets/modelData/gob/gob_walk.tka");
	anim[0].SetLoopFlag(true);
	SkinModelRender* sr = NewGO<SkinModelRender>(0, "sr");
	sr->Init(L"Assets/modelData/gob_bone.cmo", anim, 1);
	sr->SetScale({ 10,10,10 });*/


	SkinModelRender* sm = NewGO<SkinModelRender>(0, "sm");
	sm->Init(L"Assets/modelData/tesEnemy3.cmo");
	sm->SetPosition(CVector3::Zero());
	sm->SetScale({ 0.001f,0.001f,0.001f });


	//MainRoop
	Engine::IEngine().GameRoop();
	//Release
	Engine::IEngine().Final();
}
