#include "stdafx.h"
#include "NetPVPMode.h"

#include "../Title/ModeSelect.h"

#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"
#include "../ExchangeData/ExchangeData.h"

NetPVPMode::NetPVPMode()
{
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	Engine::IEngine().CreateNetworkSystem();
	m_exdata = new ExchangeData();
	m_exdata->sendData("asdfasdfasd");
}

bool NetPVPMode::Start() {
	return true;
}

void NetPVPMode::OnDestroy()
{
	Engine::IEngine().DestroyNetworkSystem();
}


void NetPVPMode::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		Engine::IEngine().GetNetworkLogic()->GetLBL()->raiseSomeEvent();
	}
}