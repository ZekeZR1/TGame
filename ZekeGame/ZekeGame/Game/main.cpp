#include "stdafx.h"
#include "Game.h"
#include "GameCamera3D.h"
#include "GameCamera2D.h"
#include "Title/pvpModeSelect.h"
#include "Title/ModeSelect.h"
#include "../TestScene.h"
#include "Fade/Fade.h"
#include "NetPVP\NetPVPMode.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	//Initialize
	Engine::IEngine().Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	//NewGO<Game>(0,"Game");
	NewGO<PvPModeSelect>(0, "pvp");
	NewGO<Fade>(0, "fade");
	NewGO<GameCamera3D>(0, "cam3d");
	NewGO<GameCamera2D>(0, "cam2d");
	//NewGO<NetPVPMode>(0, "modesel");
	g_physics.SetDebugDraw(true);
	SkinModelRender* sm = NewGO<SkinModelRender>(0, "sm");
	sm->Init(L"Assets/modelData/tesEnemy3.cmo");
	sm->SetPosition(CVector3::Zero());
	sm->SetScale({ 0.001f,0.001f,0.001f });
	//MainRoop
	Engine::IEngine().GameRoop();
	//Release
	Engine::IEngine().Final();
}
