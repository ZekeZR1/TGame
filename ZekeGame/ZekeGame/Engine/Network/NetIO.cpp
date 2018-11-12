#include "stdafx.h"
#include "NetIO.h"


NetIO::NetIO()
{
}


NetIO::~NetIO()
{
	mp_networkLogic->setLastInput(INPUT_EXIT);
	mExit = true;
	#if defined _EG_EMSCRIPTEN_PLATFORM
		emscripten_force_exit(0);
	#endif
}

void NetIO::start() {

}

void NetIO::update(NetworkLogic* networklogic) {

	mp_networkLogic = networklogic;

	//TODO : ƒQ[ƒ€‘¤‘¤‚Å‚Ì“üŽèo—Í‚ðŠÇ—‚·‚é
//	if (g_pad[0].IsTrigger(enButtonUp)) {
//		mp_networkLogic->setLastInput(INPUT_1);
//	}
//	else if (g_pad[0].IsTrigger(enButtonRight)) {
//		mp_networkLogic->setLastInput(INPUT_2);
//	}
//	else if (g_pad[0].IsTrigger(enButtonDown)) {
//		mp_networkLogic->setLastInput(INPUT_3);
//	}
//	else if (g_pad[0].IsTrigger(enButtonLeft)) {
//		mp_networkLogic->setLastInput(INPUT_4);
//	}
//	else {
//		mp_networkLogic->setLastInput(Input::INPUT_NON);
//	}
//	
	//case 'h':
	//	usage();

	mp_networkLogic->run();
	Console::get().update();
}


void NetIO::usage() {
#if defined _EG_PS4_PLATFORM || defined _EG_PSVITA_PLATFORM
	Console::get().writeLine(L"Photon LoadBalancing Demo");
	Console::get().writeLine(L"usage:");
	Console::get().writeLine(L"always:");
	Console::get().writeLine(L" Triangle - print this help");
	Console::get().writeLine(L" Circle - exit");
	Console::get().writeLine(L"--------------------");
	Console::get().writeLine(L"outside a game room:");
	Console::get().writeLine(L" Cross - create game");
	Console::get().writeLine(L" Square - join random game or last joined game");
	Console::get().writeLine(L" L2 - create direct \"all to all\" game");
	Console::get().writeLine(L" R2 - create direct \"master to all\" game");
	Console::get().writeLine(L"--------------------");
	Console::get().writeLine(L"inside a game room:");
	Console::get().writeLine(L" Cross - leave game");
	Console::get().writeLine(L" Square - leave game (will come back - disconnects and quits)");
	Console::get().writeLine(L"--------------------");
#else
	Console::get().writeLine(L"Photon LoadBalancing Demo");
	Console::get().writeLine(L"usage:");
	Console::get().writeLine(L"always:");
	Console::get().writeLine(L" h - print this help");
	Console::get().writeLine(L" 0 - exit");
	Console::get().writeLine(L"--------------------");
	Console::get().writeLine(L"outside a game room:");
	Console::get().writeLine(L" 1 - create game");
	Console::get().writeLine(L" 2 - join random game or last joined game");
	Console::get().writeLine(L" 3 - create direct \"all to all\" game");
	Console::get().writeLine(L" 4 - create direct \"master to all\" game");
	Console::get().writeLine(L"--------------------");
	Console::get().writeLine(L"inside a game room:");
	Console::get().writeLine(L" 1 - leave game");
	Console::get().writeLine(L" 2 - leave game (will come back - disconnects and quits)");
	Console::get().writeLine(L"--------------------");
#endif
}