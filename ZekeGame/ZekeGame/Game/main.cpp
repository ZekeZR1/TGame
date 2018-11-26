#include "stdafx.h"
#include "Game.h"
#include "Title/pvpModeSelect.h"
#include "Title/ModeSelect.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	//Initialize
	Engine::IEngine().Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	//NewGO<Game>(0,"Game");
	//NewGO<PvPModeSelect>(0, "pvp");
	NewGO<ModeSelect>(0, "modesel");
	//MainRoop
	Engine::IEngine().GameRoop();
	//Release
	Engine::IEngine().Final();
}
