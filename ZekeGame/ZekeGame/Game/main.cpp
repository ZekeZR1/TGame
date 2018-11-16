#include "stdafx.h"
#include "Game.h"
#include "Title/pvpModeSelect.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	//Initialize
	Engine::IEngine().Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	NewGO<Game>(0,"Game");
	NewGO<PvPModeSelect>(0, "pvp");
	//MainRoop
	Engine::IEngine().GameRoop();
	//Release
	Engine::IEngine().Final();
}
