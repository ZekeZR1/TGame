// ñºÇÕGameÇ∆ê\Ç∑ÅB

#include "stdafx.h"
#include "Dungeon/DungeonData.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameData.h"
#include "GameMenu/GameMenu.h"
#include "PythonBridge/PythonBridge.h"
#include "Monster/Monster.h"
#include "Monster/MonsterActionManeger.h"
#include "Monster/Monsters/TestMons.h"
#include "Result/Win/Win.h"
#include "Result/DungeonResult.h"


void Game::GamePVPmodeInit(std::vector<std::string> files, int monsterAI[6],MonsterID MonsterID[6])
{
	ss = new StageSetup();
	ss->PVPSetup(files, monsterAI,MonsterID);
	m_playMode = enLocalPVP;
}

bool Game::Start() {
	m_pi = new Pyinit;
	NewGO<MonsterActionManeger>(0, "MAM");
	m_model = NewGO<SkinModelRender>(0, "model");
	m_model->Init(L"Assets/modelData/dun.cmo");
	m_model->SetPosition(CVector3::Zero());
	m_menu = NewGO<GameMenu>(0, "gm");
	m_menu->init(m_playMode,m_dunNum);
	if(m_isOnlineGame)
		Engine::IEngine().CreateNetworkSystem();
	camera = new GameCamera;

	m_smd = NewGO<SkinModelDummy>(0, "smd");
	m_smd->Init(L"Assets/modelData/limit.cmo", enFbxUpAxisZ);
	m_smd->SetPosition(CVector3::Zero());
	m_smd->CreatePhysicsStaticObject();

	OutputDebugStringA("Start Battle");

	m_fr = NewGO<FontRender>(0, "fr");
	return true;
}

void Game::OnDestroy() {
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		DeleteGO(mon);
	}
	DeleteGO(m_model);
	DeleteGO(m_sprite);
	DeleteGO(FindGO<SkinModelRender>("stageModel"));
	if(m_isOnlineGame)
		Engine::IEngine().DestroyNetworkSystem();
	delete m_pi;
}

void Game::Update() {
	if (m_END)
		return;
	if (m_suddenDeath)
	{
		for (auto mon : g_mons)
		{
			if (mon == NULL)
				break;
			float hp = mon->GetHP() - 0.005f;
			mon->SetHP(hp);
		}
	}
	else
	{
		if (m_time < 0)
		{
			/*const char* files[6];
			MonsterID monids[6];
			int team[6];
			for (int i = 0; i < 6; i++)
			{
				Monster* mon = g_mons[i];
				if (mon == NULL)
					break;

				files[i] = mon->GetpyFile();
				monids[i] = (MonsterID)mon->GetID();
				team[i] = mon->Getteam();

			}*/
			//StageSetup::SuddenDeath(files, monids, team);
			for (auto mon : g_mons)
			{
				if (mon == NULL)
					break;
				float maxhp = mon->GetMaxHP() / 10;
				float hp = maxhp * mon->GetHP() / mon->GetMaxHP();
				mon->SetMaxHP(maxhp);
				mon->SetHP(hp);

			}
			SuddenDeath();
			DeleteGO(m_fr);
		}
		else
		{
			int m = m_time / 60;
			float s = m_time - m * 60;
			wchar_t text[255];

			swprintf_s(text, L"%02d:%02.2f", m, s);
			m_fr->Init(text, {440,360 }, 0, CVector4::White, 1, {0,0 });
			m_time -= IGameTime().GetFrameDeltaTime();
		}
	}
	
	if (m_menu->isOpen())
		return;
	

	camera->SetTarget(CVector3::Zero());
	camera->SetPosition({ 0.0f, 350.0f, 1000.0f });
	camera->Update();
	if (g_buddyCount == 0 || g_enemyCount == 0)
	{
		m_END = true;
		int team = g_mons[0]->Getteam();
		DeleteGO(m_menu);
		m_menu = nullptr;
		QueryGOs<Monster>("monster", [&](auto obj)->bool
		{
			obj->ReleaseMAL();
			return true;
		});
		switch (m_playMode)
		{
		case enLocalPVP:
		{
			auto win = NewGO<Win>(0, "win");
			win->init(team);
			break;
		}
		case enRandomPVP:
			break;
		case enDungeon:
		{
			auto dr = NewGO<DungeonResult>(0, "dr");
			dr->init(team, m_dunNum);
			break;
		}
		}
	}
	
}
