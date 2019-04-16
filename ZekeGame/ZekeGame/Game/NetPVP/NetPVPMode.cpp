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
	//test
	//for (int i = 3; i < 6; i++) {
	//	m_monai[i] = 0;
	//	m_moid[i] = 2;
	//}
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
	 OutputDebugString(str);
	 if (onlinePlayerNum == 2) {
		 RaiseData();
		 LoadEnemyData();
	 }
	 if (m_dataLoaded) {
		 for (int i = 3; i < 6; i++) {
			 m_monai[i] = 0;
			 m_moid[i] = m_enemyId[i - 3];
		 }
		 BattleStart();
	 }
//#if _DEBUG
//	if (g_pad[0].IsTrigger(enButtonA))
//		RaiseData();
//#endif
//	//m_isConect = m_exdata->isConect();
//	//if (m_isConect) {
//	//	//OutputDebugString("Matching!!!!!! \n");
//	//}
//	//if (!m_isConect) {
//	//	//OutputDebugString("WAITING \n");
//	//	return;
//	//}
//	if (Engine::IEngine().GetNetworkLogic()->GetLBL()->GetOnlinePlayerCount() != 2) {
//		char str[256];
//		sprintf_s(str, "active online user num is %d\n", Engine::IEngine().GetNetworkLogic()->GetLBL()->GetOnlinePlayerCount());
//		OutputDebugString(str);
//		return;
//	}
//	m_informationSp->Init(L"Assets/Sprite/ready.dds", 300.f, 50.f);
//	RaiseData();
//	LoadEnemyData();
//	if (m_dataLoaded && m_dataRaised) {
//		for (int i = 3; i < 6; i++) {
//			m_monai[i] = 0;
//			m_moid[i] = m_enemyId[i - 3];
//		}
//		BattleStart();
//	}
}

void NetPVPMode::RaiseData() {
	//if (m_dataRaised)
		//return;
	//MonsterData
	int ids[3];
	for (int i = 0; i < 3; i++) {
		ids[i] = m_moid[i];
		char str[256];
		sprintf_s(str, "raise id is %d\n", ids[i]);
		OutputDebugString(str);
	}
	auto lbl = Engine::IEngine().GetNetworkLogic()->GetLBL();
	lbl->SetTeamMonsterInfo(ids);
	lbl->raiseMonData();
	//m_dataRaised = true;
	//Engine::IEngine().GetNetworkLogic()->GetLBL()->SetTeamMonsterInfo(ids);
	/*for (int i = 0; i < 3; i++) {
		m_exdata->sendMonData(i, m_monai[i]);
		Engine::IEngine().GetNetworkLogic()->GetLBL()->raiseMonData();
		OutputDebugString("raise monster data\n");
	}*/
	//Monster Code

	//if(raiseMonData){
}

void NetPVPMode::LoadEnemyData() {
	if (m_dataLoaded) 
		return;
	//if (!Engine::IEngine().GetNetworkLogic()->GetLBL()->isHang())
		//return;
	auto ids = Engine::IEngine().GetNetworkLogic()->GetLBL()->GetEnemyTeamIDs();
	if (ids[0] == 0)
		return;
	for (int i = 0; i < 3; i++) {
		m_enemyId[i] = ids[i];
		OutputDebugString("LOADING ENEMY TEAM MONSTER ID DATAS\n");
	}
	m_dataLoaded = true;
	/*int num = Engine::IEngine().GetNetworkLogic()->GetLBL()->GetMonNum();
	int id = Engine::IEngine().GetNetworkLogic()->GetLBL()->GetMonID();
	char str[256];
	sprintf_s(str, "Monster NUM is %d !!!!!! MOOONnster ID is %d\n", num, id);
	OutputDebugString(str);
	m_enemyId[num] = id;
	if (m_enemyId[0] != -1 &&
		m_enemyId[1] != -1 &&
		m_enemyId[2] != -1) {*/
		//m_dataLoaded = true;
	//}
}

void NetPVPMode::BattleStart() {
	auto game = NewGO<Game>(0, "Game");
	StageSetup::NetworkPvPSetup(m_files, m_monai, m_moid);
	DeleteGO(this);
}