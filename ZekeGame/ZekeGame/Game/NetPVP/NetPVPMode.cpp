#include "stdafx.h"
#include <fstream>
#include "NetPVPMode.h"
#include "../Title/ModeSelect.h"
#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"
#include "../ExchangeData/ExchangeData.h"
#include "NetAISelect.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "../Game.h"

NetPVPMode::NetPVPMode()
{
	Engine::IEngine().CreateNetworkSystem();
	m_lbl = Engine::IEngine().GetNetworkLogic()->GetLBL();
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
}

void NetPVPMode::init(std::vector<std::string> files, int monai[3], int moid[3])
{
	for (int i=0;i<3;i++)
	{
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
	 auto lbl = Engine::IEngine().GetNetworkLogic()->GetLBL();
	 RaiseData();
	 LoadEnemyData();
	 if (m_dataLoaded) {
		 for (int i = 3; i < 6; i++) {
			 m_monai[i] = i - 3;
			 m_moid[i] = m_enemyId[i - 3];
		 }
		 BattleStart();
	 }
	 //Test
	 if (g_pad[0].IsTrigger(enButtonA)) {
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
	RaiseAiTextData();
}

void NetPVPMode::LoadEnemyData() {
	if (m_dataLoaded) 
		return;
	//Load Enemy Ids
	auto ids = m_lbl->GetEnemyTeamIDs();
	if (ids[0] == 0)
		return;
	for (int i = 0; i < 3; i++) {
		m_enemyId[i] = ids[i];
		OutputDebugString("LOADING ENEMY TEAM MONSTER ID DATAS\n");
	}
	//Load Enemy AIs
	if(m_lbl->isGotEnemyPythonCodes())
		m_dataLoaded = true;
}

void NetPVPMode::BattleStart() {
	auto game = NewGO<Game>(0, "Game");
	game->SetRandomPVPMode();
	auto enemyFiles = PythonFileLoad::FilesLoadOnlineEnemy();
	StageSetup::NetworkPvPSetup(m_files, enemyFiles, m_monai, m_moid);
	DeleteGO(this);
}

void NetPVPMode::RaiseAiTextData() {
	if (!m_myAIsLoaded) {
		for (int i = 0; i < 3; i++) {
			char cd[255] = { '\0' };
			GetCurrentDirectoryA(255, cd);
			std::string path = "\\PythonAIs\\";
			path += m_files[i];
			char* cstr = new char[path.size() + 1];
			std::char_traits<char>::copy(cstr, path.c_str(), path.size() + 1);
			strcat(cd, cstr);
			strcat(cd, ".py");
			OutputDebugString("PYTHON CODE RAISED!! PATH IS \n");
			OutputDebugString(cd);
			OutputDebugString("\n");
			delete[] cstr;
			FILE* file;
			fpos_t pos;
			file = fopen(cd, "r");
			fseek(file, 0, SEEK_END);
			fgetpos(file, &pos);
			long size = pos;
			fseek(file, 0, SEEK_SET);
			char text[1024] = { '\0' };
			fread(text, size, 1, file);
			fclose(file);
			OutputDebugString(text);
			m_lbl->SetText(text, i);
			m_myAIsLoaded = true;
		}
	}
	m_lbl->raiseMonAIs();
}