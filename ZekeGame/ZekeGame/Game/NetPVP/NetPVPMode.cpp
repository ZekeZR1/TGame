#include "stdafx.h"
#include "NetPVPMode.h"
#include "../Title/ModeSelect.h"
#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"
#include "../ExchangeData/ExchangeData.h"
#include "NetAISelect.h"
#include "../Game.h"

NetPVPMode::NetPVPMode()
{
	Engine::IEngine().CreateNetworkSystem();
	//NewGO<NetAISelect>(0, "pvp");
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
	m_informationSp = NewGO<SpriteRender>(0);
	m_informationSp->Init(L"Assets/Sprite/waiting.dds",300.f,50.f);
	m_informationSp->SetPosition(m_informationPos);
	return true;
}

void NetPVPMode::OnDestroy()
{
	DeleteGO(m_informationSp);
	Engine::IEngine().DestroyNetworkSystem();
}


void NetPVPMode::Update() {
	 char str[256];
	 int onlinePlayerNum = Engine::IEngine().GetNetworkLogic()->GetLBL()->GetOnlinePlayerCount();
	 sprintf_s(str, "active online user num is %d\n", onlinePlayerNum);
	 //OutputDebugString(str);
	 auto lbl = Engine::IEngine().GetNetworkLogic()->GetLBL();
	 RaiseData();
	 LoadEnemyData();
	 //if (onlinePlayerNum == 2 || lbl->isHang()) {
	 //}
	 if (m_dataLoaded) {
		 for (int i = 3; i < 6; i++) {
			 m_monai[i] = 0;
			 m_moid[i] = m_enemyId[i - 3];
		 }
		 BattleStart();
	 }
}

void NetPVPMode::RaiseData() {
	//Raise Monster ids
	int ids[3];
	for (int i = 0; i < 3; i++) 
		ids[i] = m_moid[i];
	auto lbl = Engine::IEngine().GetNetworkLogic()->GetLBL();
	lbl->SetTeamMonsterInfo(ids);
	lbl->raiseMonData();
	//Raise Monster AIs

}

void NetPVPMode::LoadEnemyData() {
	if (m_dataLoaded) 
		return;
	//Load Enemy Ids
	auto ids = Engine::IEngine().GetNetworkLogic()->GetLBL()->GetEnemyTeamIDs();
	if (ids[0] == 0)
		return;
	for (int i = 0; i < 3; i++) {
		m_enemyId[i] = ids[i];
		OutputDebugString("LOADING ENEMY TEAM MONSTER ID DATAS\n");
	}
	//Load Enemy AIs

	m_dataLoaded = true;
}

void NetPVPMode::BattleStart() {
	auto game = NewGO<Game>(0, "Game");
	StageSetup::NetworkPvPSetup(m_files, m_monai, m_moid);
	DeleteGO(this);
}