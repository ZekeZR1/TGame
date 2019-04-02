#include "stdafx.h"
#include "NetPVPMode.h"

#include "../Title/ModeSelect.h"

#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"
#include "../ExchangeData/ExchangeData.h"

NetPVPMode::NetPVPMode()
{
	char cd[255] = { '\0' };
	GetCurrentDirectoryA(255, cd);
	strcat(cd, "\\PythonAIs\\fuckinAI.py");
	
	FILE* file;
	fpos_t pos;
	file = fopen(cd, "r");
	fseek(file, 0, SEEK_END);
	fgetpos(file, &pos);
	long size = pos;
	fseek(file, 0, SEEK_SET);
	char text[1024] = {'\0'};
	fread(text, size,1, file);
	fclose(file);



	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	Engine::IEngine().CreateNetworkSystem();
	m_exdata = new ExchangeData();
	m_exdata->sendData(text);
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