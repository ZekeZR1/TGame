#include "stdafx.h"
#include "NetPVPMode.h"

#include "../Title/ModeSelect.h"

#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"
#include "../ExchangeData/ExchangeData.h"

#include "NetAISelect.h"

NetPVPMode::NetPVPMode()
{
	NewGO<NetAISelect>(0, "pvp");
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

void NetPVPMode::init(std::vector<std::string> files, int monai[3], int moid[3])
{
	for (int i=0;i<3;i++)
	{
		bool OK = true;
		for (auto s : m_files)
		{
			if (s == files[monai[i]])
			{
				OK = false;
				break;
			}
		}
		if (OK)
			m_files.push_back(files[monai[i]]);

		m_monai[i] = monai[i];
		m_moid[i] = moid[i];
	}


}

bool NetPVPMode::Start() {
	return true;
}

void NetPVPMode::OnDestroy()
{
	Engine::IEngine().DestroyNetworkSystem();
}


void NetPVPMode::Update() {
	m_isConect = m_exdata->isConect();

	if (m_isConect)
	{

	}

	if (g_pad[0].IsTrigger(enButtonA)) {
		Engine::IEngine().GetNetworkLogic()->GetLBL()->raiseSomeEvent();
	}
	else if (g_pad[0].IsTrigger(enButtonB))
	{
		m_exdata->sendMonData(1, 3);
		Engine::IEngine().GetNetworkLogic()->GetLBL()->raiseMonData();
	}
}