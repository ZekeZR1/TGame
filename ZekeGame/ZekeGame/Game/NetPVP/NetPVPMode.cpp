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
	m_isConect = m_exdata->isConect();
	if (m_isConect) {
		//OutputDebugString("Matching!!!!!! \n");
	}
	if (!m_isConect) {
		//OutputDebugString("WAITING \n");
		return;
	}

	m_informationSp->Init(L"Assets/Sprite/ready.dds", 300.f, 50.f);
	RaiseData();
	LoadEnemyData();
	if (m_dataLoaded && m_dataRaised) {
		for (int i = 3; i < 6; i++) {
			m_moid[i] = m_enemyId[i];
		}
		BattleStart();
	}
}

void NetPVPMode::RaiseData() {
	if (m_dataRaised)
		return;
	//MonsterData
	for (int i = 0; i < 3; i++) {
		m_exdata->sendMonData(i, m_monai[i]);
		Engine::IEngine().GetNetworkLogic()->GetLBL()->raiseMonData();
	}
	//Monster Code

	//if(raiseMonData){
	m_dataRaised = true;
}

void NetPVPMode::LoadEnemyData() {
	if (m_dataLoaded) 
		return;
	int num = Engine::IEngine().GetNetworkLogic()->GetLBL()->GetMonNum();
	int id = Engine::IEngine().GetNetworkLogic()->GetLBL()->GetMonID();
	m_enemyId[num] = id;
	if (m_enemyId[0] != -1 ||
		m_enemyId[1] != -1 ||
		m_enemyId[2] != -1) {
		m_dataLoaded = true;
	}
}

void NetPVPMode::BattleStart() {
	auto game = NewGO<Game>(0, "Game");
	StageSetup::NetworkPvPSetup(m_files,m_moid,m_monai,m_enemyId);
	DeleteGO(this);
}