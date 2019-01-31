// 名はGameと申す。

#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameData.h"
#include "GameMenu/GameMenu.h"


#include "PythonBridge/PythonBridge.h"
#include "Monster/Monster.h"
#include "Monster/MonsterActionManeger.h"
#include "Monster/Monsters/TestMons.h"
//#include "Monster/MonsterActionList.h"


#include "Result/Win/Win.h"
#include "Result/DungeonResult.h"

Game::Game()
{
}


Game::~Game()
{
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		DeleteGO(mon);
	}
	DeleteGO(m_model);
	DeleteGO(m_sprite);
	DeleteGO(FindGO<SkinModelRender>("stageModel"));
	Engine::IEngine().DestroyNetworkSystem();
	delete m_pi;
}

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
	m_model->Init(L"Assets/modelData/map.cmo");
	m_model->SetPosition(CVector3::Zero());

	m_menu = NewGO<GameMenu>(0, "gm");
	m_menu->init(m_playMode,m_dunNum);

	/*m_sprite = NewGO<SpriteRender>(0,"sprite");
	m_sprite->Init(L"Assets/Sprite/Test.dds", 500.f, 500.f);
	m_sprite->SetPosition(CVector3::Zero());*/

	Engine::IEngine().CreateNetworkSystem();

	camera = new GameCamera;

	return true;
}
void Game::Update() {
	static CVector3 pos = CVector3::Zero();
	/*if (g_pad[0].IsPress(enButtonDown)) {
		pos.x += 50.0f;
	}*/
	
	if (!m_END)
	{
		if (m_menu->isOpen())
			return;
		m_model->SetPosition(pos);
		camera->SetTarget(CVector3::Zero());
		camera->SetPosition({ 0.0f, 350.0f, 1000.0f });
		camera->Update();
		if (g_buddyCount == 0 || g_enemyCount == 0)
		{
			m_END = true;
			int team = g_mons[0]->Getteam();
			Win* win;
			DungeonResult* dr;
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
				win = NewGO<Win>(0,"win");
				win->init(team);
				break;
			case enRandomPVP:

				break;
			case enDungeon:
				dr = NewGO<DungeonResult>(0, "dr");
				dr->init(team, m_dunNum);
				break;
			}
		}
	}
}

void Game::Render() {
}

void Game::PostRender() {
}