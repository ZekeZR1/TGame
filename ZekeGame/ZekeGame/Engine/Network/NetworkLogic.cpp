#include "stdafx.h"
#include "NetworkLogic.h"
#include "LoadBalancingListener.h"
#include "LoadBalancing-cpp/inc/Client.h"
#include "TestView.h"

static const ExitGames::Common::JString appID = L"548e2b85-0a39-45bb-a62b-d0e96ad8eb96";
static const ExitGames::Common::JString appVersion = L"1.0";

static ExitGames::Common::JString gameName = L"Basics";

static const ExitGames::Common::JString PLAYER_NAME = L"user";
static const int MAX_SENDCOUNT = 100;

using namespace ExitGames::LoadBalancing;
using namespace ExitGames::Common;
using namespace ExitGames::Photon;


NetworkLogic::NetworkLogic()
{
}


NetworkLogic::~NetworkLogic()
{
}



void NetworkLogic::Disconnect() {
	mpLbl->disconnect();
}

void NetworkLogic::Start() {
	//BaseViewの仮想関数を定義したクラスのポインタを渡す
	//LoadBalancingからそれらを呼び出す
	mpLbl = new LoadBalancingListener(&m_testview);
	mpLbc = new Client(*mpLbl, appID, appVersion);
	mpLbc->setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	ExitGames::Common::Base::setListener(mpLbl);
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS));
	//	pLbc->setCRCEnabled(true);
	mpLbl->setLBC(mpLbc);
	mpLbc->setTrafficStatsEnabled(true);
	Console::get().writeLine(L"LBC: connecting...");
	mpLbl->connect(JString(L"NV") + GETTIMEMS());
}

void NetworkLogic::Update() {
	mpLbc->service();
	mpLbl->service();
}

