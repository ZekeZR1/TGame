// ñºÇÕGameÇ∆ê\Ç∑ÅB

#include "stdafx.h"
#include "Dungeon/DungeonData.h"
#include "Game.h"
#include "Dungeon/DungeonGame.h"
#include "GameCamera.h"
#include "GameData.h"
#include "GameMenu/GameMenu.h"
#include "PythonBridge/PythonBridge.h"
#include "Monster/Monster.h"
#include "Monster/MonsterActionManeger.h"
#include "Monster/Monsters/TestMons.h"
#include "Result/Win/Win.h"
#include "Result/DungeonResult.h"
#include "NetPVP/CRatingSystem.h"
#include "ReadyGO/ReadyGO.h"

#include "Fade/Fade.h"
#include "Fade/MusicFade.h"

void Game::GamePVPmodeInit(std::vector<std::string> files, int monsterAI[6],MonsterID MonsterID[6])
{
	//StageSetup::PVPSetup(files, monsterAI,MonsterID);
	m_playMode = enLocalPVP;
}

bool Game::Start() {
	m_BGM = NewGO<Sound>(0, "BGM");
	m_BGM->Init(L"Assets/sound/BGM/bgm_maoudamashii_fantasy12.wav", true);
	m_BGM->SetVolume(0.3f);
	m_BGM->Play();

	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	m_fade->SetSpeed(5);

	m_pi = new Pyinit;
	NewGO<MonsterActionManeger>(0, "MAM");
	m_model = NewGO<SkinModelRender>(0, "model");
	m_model->SetShadowCasterFlag(false);
	m_model->Init(L"Assets/modelData/dun.cmo",nullptr, 0, enFbxUpAxisZ, "PSMainStage");
	m_model->SetPosition(CVector3::Zero());

	m_floor = NewGO<SkinModelRender>(0, "model");
	m_floor->Init(L"Assets/modelData/dun_yuka.cmo");
	m_floor->SetPosition(CVector3::Zero());

	m_menu = NewGO<GameMenu>(0, "gm");
	m_menu->init(m_playMode,m_dunNum);
	if (m_isOnlineGame) {
		//Engine::IEngine().CreateNetworkSystem();
	}
	camera = new GameCamera;

	m_smd = NewGO<SkinModelDummy>(0, "smd");
	m_smd->Init(L"Assets/modelData/limit2.cmo", enFbxUpAxisZ);
	m_smd->SetPosition(CVector3::Zero());
	m_smd->CreatePhysicsStaticObject();

	OutputDebugStringA("Start Battle");

	m_frS = NewGO<FontRender>(0, "fr");
	m_fr = NewGO<FontRender>(0, "fr");


	e = NewGO<CEffect>(0, "s");
	e->SetPosition(CVector3::Zero());
	e->SetScale({ 500,500,500 });
	e->Play(L"Assets/effect/l/laser.efk");

	if (m_playMode == enDungeon) {
		int round = IDungeonData().GetNumRound(m_dunNum);
		auto dg = FindGO<DungeonGame>("DungeonGame");
		int current = dg->GetCurrentRound();
		wchar_t str[256];
		swprintf_s(str, L"Dungeon %d : Round %d/%d",m_dunNum + 1,current + 1, round + 1);
		m_dunInfoF = NewGO<FontRender>(0);
		m_dunInfoF->Init(str, { -360,370 });
		m_dunInfoF->DrawShadow();
	}
	return true;
}

void Game::OnDestroy() {
	//m_BGM->Stop();
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		DeleteGO(mon);
	}
	DeleteGO(m_model);
	DeleteGO(m_sprite);
	DeleteGO(FindGO<SkinModelRender>("stageModel"));
	DeleteGO(m_fr);
	DeleteGO(m_frS);
	DeleteGO(m_floor);
	DeleteGO(m_smd);
	DeleteGO(m_dunInfoF);
	if (m_isOnlineGame) {
		//Engine::IEngine().DestroyNetworkSystem();
	}
	RatingSystem().ClosePopup();
	delete m_pi;

	if(camera!=nullptr)
		delete camera;
}

void Game::Update() {
	if (!m_fade->isFadeStop())
		return;
	else if(m_Ffirst)
	{
		m_readyGO = NewGO<ReadyGO>(0, "rg");
		m_Ffirst = false;
	}
	else 
	{
		if (!m_isEndReady)
		{
			m_isEndReady = m_readyGO->IsEnd();
			if (m_isEndReady)
			{
				DeleteGO(m_readyGO);
				m_menu->DO();
			}
		}
	}
	if (m_END)
	{
		if (m_fade->isFadeStop() && !m_isGameSet)
		{
			switch (m_playMode)
			{
			case enLocalPVP:
			{
				auto win = NewGO<Win>(0, "win");
				win->init(m_winTeam, enLocalPVP);
				break;
			}
			case enRandomPVP:
			{
				auto win = NewGO<Win>(0, "win");
				win->init(m_winTeam, enRandomPVP);
				RatingSystem().SetWinner(m_winTeam);
				RatingSystem().PopupRate(m_eneRate);
				break;
			}
			case enDungeon:
			{
				auto dr = NewGO<DungeonResult>(0, "dr");
				dr->init(m_winTeam, m_dunNum);
				break;
			}
			}
			m_isGameSet = true;
			m_fade->SetSpeed(5);
		}
		return;
	}
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
			m_fr = nullptr;

			
		}
		else
		{
			int m = m_time / 60;
			float s = m_time - m * 60;
			wchar_t text[255];

			swprintf_s(text, L"%02d:%02.2f", m, s);
			m_fr->Init(text, {350,360 }, 0, CVector4::White, 1, {0,0 });
			m_frS->Init(text, { 350 + 5,360 - 5 }, 0, {0,0,0,1}, 1, { 0,0 });

			m_time -= IGameTime().GetFrameDeltaTime();
		}
	}
	
	if (m_menu->isOpen())
		return;

	bool isEne = true;
	for (int i = 0;i < 6;i++)
	{
		if (g_mons[i] == nullptr || (i == 0 && g_mons[i]->Getteam() == 1))
		{
			break;
		}
		if (0 != g_mons[i]->Getteam())
		{
			isEne = false;
			break;
		}
	}

	camera->SetTarget(CVector3::Zero());
	camera->SetPosition({ 0.0f, 350.0f, 1000.0f });
	camera->Update();
	if (isEne || g_buddyCount == 0 || g_enemyCount == 0)
	{
		m_END = true;

		delete camera;
		camera = nullptr;
		m_fade->SetSpeed(0.5f);
		m_fade->FadeOut();
		MusicFade* mf = NewGO<MusicFade>(0, "mf");
		mf->init(m_BGM,0.15f);

		m_winTeam = g_mons[0]->Getteam();
		DeleteGO(m_menu);
		m_menu = nullptr;

		QueryGOs<Monster>("monster", [&](auto obj)->bool
		{
			obj->ReleaseMAL();
			return true;
		});
		
	}
	
}
