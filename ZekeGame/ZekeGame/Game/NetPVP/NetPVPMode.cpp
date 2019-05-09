#include "stdafx.h"
#include <fstream>
#include "CRatingSystem.h"
#include "NetPVPMode.h"
#include "../Title/ModeSelect.h"
#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"
#include "../ExchangeData/ExchangeData.h"
#include "NetAISelect.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "../Online/NetworkLogic.h"
#include "../Online/Console.h"
#include "../Game.h"

NetPVPMode::NetPVPMode()
{
	//Engine::IEngine().CreateNetworkSystem();
	NetSystem().CreateNetworkSystem();
	m_lbl = NetSystem().GetNetworkLogic().GetLBL();
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
}

void NetPVPMode::init(std::vector<std::string> files, int monai[3], int moid[3],int aimode[3])
{
	for (int i=0;i<3;i++)
	{
		m_files.push_back(files[monai[i]]);
		m_monai[i] = monai[i];
		m_moid[i] = moid[i];
		m_aimode[i] = aimode[i];
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
	NetSystem().DestroyNetworkSystem();
}


void NetPVPMode::Update() {
	NetSystem().GetNetworkLogic().Update();
	 RaiseData();
	 LoadEnemyData();
	 if (m_dataLoaded) {
		 auto eneaimode = m_lbl->GetEnemyAiModes();
		 for (int i = 3; i < 6; i++) {
			 m_monai[i] = i - 3;
			 m_moid[i] = m_enemyId[i - 3];
			 m_aimode[i] = eneaimode[i - 3];
		 }
		 m_isfade = true;
		 if(!m_isfade)
			m_fade->FadeOut();
	 }
	 if (m_fade->isFadeStop() && m_isfade) {
		 BattleStart();
	 }
	 //Test
#if _DEBUG
	 if (g_pad[0].IsTrigger(enButtonA)) {
		 m_isfade = true;
		 if (!m_isfade)
			 m_fade->FadeOut();
	 }
#endif
	 if (m_isBackFade && m_fade->isFadeStop()) {
		 BackToMenu();
	 }
}

void NetPVPMode::RaiseData() {
	//Raise Monster ids
	int ids[3];
	for (int i = 0; i < 3; i++) 
		ids[i] = m_moid[i];
	m_lbl->SetTeamMonsterInfo(ids);
	m_lbl->raiseMonData();
	for (int i = 0; i < 3; i++) {
		m_lbl->SetAiMode(m_aimode[i],i);
	}
	//Raise Monster AIs
	RaiseAiVaData();
	RaiseAiTextData();
	RaiseRatingData();
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
	//Load Enemy AIs (including va)
	if(m_lbl->isGotEnemyPythonCodes())
		m_dataLoaded = true;
}

void NetPVPMode::BattleStart() {
	auto game = NewGO<Game>(0, "Game");
	game->SetRandomPVPMode(m_lbl->GetEnemyRate());
	auto enemyFiles = PythonFileLoad::FilesLoadOnlineEnemy();
	StageSetup::NetworkPvPSetup(m_files, enemyFiles, m_monai, m_moid,m_aimode);
	DeleteGO(this);
}

void NetPVPMode::RaiseAiTextData() {
	if (!m_myPyAIsLoaded) {
		for (int i = 0; i < 3; i++) {
			if (m_aimode[i] != 0) continue;

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
			m_myPyAIsLoaded = true;
		}
	}
	m_lbl->raiseMonAIs();
}


void NetPVPMode::RaiseAiVaData() {
	using namespace std;
	auto vaFiles = VisualAiFileLoad::FilesLoad();
	if (!m_myVaAIsLoaded){
		for (int i = 0; i < 3; i++) {
			if (m_aimode[i] == 0) continue;
			char cd[255] = { '\0' };
			GetCurrentDirectoryA(255, cd);
			std::string path = "\\Assets\\VisualAI\\";
			path += vaFiles[m_monai[i]];
			path += ".va";
			char* cstr = new char[path.size() + 1];
			std::char_traits<char>::copy(cstr, path.c_str(), path.size() + 1);
			strcat(cd, cstr);
			delete[] cstr;
			ifstream ifs(cd, ios::in | ios::binary);
			if (!ifs) abort();
			int datas[1024] = { 0 };
			for (int k = 0; k < 1024; k++) {
				int x;
				ifs.read((char*)& x, sizeof(int));
				datas[k] = x;
			}
			ifs.close();
			m_lbl->SetAiMode(m_aimode[i], i);
			m_lbl->SetVisualAiData(datas, i);
			m_myVaAIsLoaded = true;
			OutputDebugString("Visual AI Data loaded!! setting lbl...\n");
			OutputDebugString(cd);
			OutputDebugString("\n");
		}
	}
	m_lbl->raiseVisualAIsData();
}

void NetPVPMode::RaiseRatingData() {
	m_lbl->raiseRating();
}

void NetPVPMode::BackToMenu() {
	NewGO<NetAISelect>(0);
	DeleteGO(this);
}
