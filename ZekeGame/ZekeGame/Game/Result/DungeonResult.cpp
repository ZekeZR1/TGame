#include "stdafx.h"
#include "../Fade/Fade.h"
#include "../GameData.h"
#include "../Game.h"
#include "../Monster/Monster.h"
#include "../Dungeon/DungeonSelect.h"
#include "ResultCamera.h"
#include "../GameCursor.h"
#include  <fstream>
#include "DungeonResult.h"
#include "../Dungeon/DungeonData.h"
#include "../Dungeon/DungeonTransition.h"
#include "../Dungeon/DungeonGame.h"
#include "../Dungeon/MonsterDrop.h"

char m_outfile[256] = "Assets/saveData/clearstate.dd";

bool DungeonResult::Start() {
	MonsterSet();
	CameraSet();
	m_fade = FindGO<Fade>("fade");
	return true;
}

void DungeonResult::OnDestroy() {
	DeleteGO(m_resultSp);
	DeleteGO(FindGO<Game>("Game"));
	DeleteGO(m_buttonSp);
	DeleteGO(m_buttonText);
	DeleteGO(m_cursor);
	DeleteGO(m_cam);
	//auto bgm = FindGO<Sound>("BGM");
	//bgm->Stop();
}

void DungeonResult::Update() {
	ButtonUpdate();
	CameraUpdate();
}

void DungeonResult::SaveDungeonClearState(){
	{
		using namespace std;
		ifstream fin("Assets/saveData/clearstate.dd", ios::in | ios::binary);
		if (!fin) {
			OutputDebugStringA("clearstate.ddÇÃÉIÅ[ÉvÉìÇ…é∏îsÇµÇ‹ÇµÇΩ");
			return;
		}
		int cleared = -1;
		fin.read(reinterpret_cast<char *>(&cleared), sizeof(int));
		char message[256];
		sprintf_s(message, "pre cleared num is %d\n", cleared);
		OutputDebugStringA(message);
		fin.close();
		ofstream fout;
		//
		char ms0[256];
		sprintf_s(ms0, "now dungeon Number is %d\n", m_dunNum);
		OutputDebugStringA(ms0);
		//
		//char ms1[256];
		//sprintf_s(ms1, "now cleared num is %d\n", cleared);
		//OutputDebugStringA(msg);
		//
		if (cleared < m_dunNum) {
			cleared += 1;
			fout.open("Assets/saveData/clearstate.dd", ios::out | ios::binary | ios::trunc);
			fout.write((char*)&cleared, sizeof(int));
		}
		fout.close();
		char msg[256];
		sprintf_s(msg, "now cleared num is %d\n", cleared);
		OutputDebugStringA(msg);
	}
}

void DungeonResult::ToNextRound() {
	int now = IDungeonData().GetRound();
	char str[256];
	sprintf_s(str, "Round %d Clear\n Go Next Round!!\n", now);
	OutputDebugStringA(str);
	int round = IDungeonData().GetRound();
	IDungeonData().SetRound(round + 1);
	int r  = IDungeonData().GetRound();
	sprintf_s(str, "Round Clear Start next Round %d\n", r);
	OutputDebugStringA(str);
	auto dGame = FindGO<DungeonGame>("DungeonGame");
	dGame->StartTransition();
	dGame->NextRound();
	OutputDebugStringA("---------------------Next Round-------------------\n");
	DeleteGO(this);
}

void DungeonResult::ToNextStage(){
	OutputDebugStringA("Stage Clear\n Start Next Duneon Stage\n");
	auto dGame = FindGO<DungeonGame>("DungeonGame");
	dGame->StartNextDungeon();
	dGame->StageClear();
	OutputDebugStringA("++++++++++++++++Next Stage++++++++++++++++++++++\n");
	//DeleteGO(dGame);
	//NewGO<DungeonSelect>(0);

	DeleteGO(this);
}

void DungeonResult::InitUI() {
	m_resultSp = NewGO<SpriteRender>(0, "resultSp");
	m_buttonSp = NewGO<SpriteRender>(0, "next");
	m_buttonSp->Init(L"Assets/Sprite/button1.dds", 300.f, 100.f, true);
	m_buttonSp->SetPosition(m_buttonPos);
	m_buttonText = NewGO<FontRender>(0);
	CVector3 textpos = m_buttonPos;
	textpos.y += 15.f;
	textpos.x += -30.f;
	m_buttonText->Init(L"OK", { textpos.x,textpos.y }, 0.f, CVector4::White, 1.f, { 0.5f,0.5f });

	if (m_team == WIN) {
		m_resultSp->Init(L"Assets/Sprite/res_win.dds", 500.f, 200.f, true);
	}
	else {
		m_resultSp->Init(L"Assets/Sprite/res_lose.dds", 500.f, 200.f, true);
	}
	//m_resultSp->SetPosition({ -410,160,0 });
	m_resultSp->SetPosition({ -410,60,0 });

	m_cursor = NewGO<GameCursor>(0);
}

void DungeonResult::Lose() {
	IDungeonData().SetRound(0);
	NewGO<DungeonSelect>(0);
	auto dGame = FindGO<DungeonGame>("DungeonGame");
	dGame->Relese();
	DeleteGO(this);
}


void DungeonResult::ToDungeonSelect() {
	IDungeonData().SetRound(0);
	NewGO<DungeonSelect>(0);
	auto dGame = FindGO<DungeonGame>("DungeonGame");
	dGame->Relese();
	DeleteGO(this);
}

void DungeonResult::MonsterSet()
{
	std::vector<Monster*> mons;
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() == m_team)
		{
			mons.push_back(mon);
		}
	}
	CVector3 poss[3] = { {0,0,0},{30,0,-10},{-30,0,-10} };
	CVector3 pos = CVector3::Zero();
	for (int i = 0; i < mons.size(); i++)
	{
		mons[i]->ReleaseMark();
		mons[i]->end();
		mons[i]->Setpos(poss[i]);
		mons[i]->SetRotation(CQuaternion::Identity());
		mons[i]->anim_idle();
	}
}

void DungeonResult::CameraSet() {
	m_cam = NewGO<ResultCamera>(0, "rescam");
	m_cam->SetPos({ 0,30,500 });
	m_cam->SetTar(CVector3::Zero());
	m_firstpos = { -350,10,500 };
	m_firsttar = { 0,30,0 };
	m_firstpos = { -350,10,500 };
	m_firsttar = { 0,30,0 };

	m_cam->SetPos(m_firstpos);
	m_cam->SetTar(m_firsttar);

	m_lastpos = { -35,50,50 };
	m_lasttar = { 0,55,0 };
	switch (g_mons[0]->GetID())
	{
	case enTest:
		break;
	case enUmataur:
		m_lastpos = { -20,150,72 };
		m_lasttar = { 30,165,0 };
		break;
	case enFairy:
		m_lastpos = { -35,90,50 };
		m_lasttar = { 0,90,0 };
		break;
	}

	m_addpos = (m_lastpos - m_firstpos) / 8.0f;
	m_addtar = (m_lasttar - m_firsttar) / 8.0f;
}

void DungeonResult::ButtonUpdate() {
	if (m_buttonSp == nullptr)
		return;
	m_buttonSp->SetCollisionTarget(m_cursor->GetCursor());
	if (Mouse::isTrigger(enLeftClick)) {
		if (m_buttonSp->isCollidingTarget()) {
			SaveDungeonClearState();
			auto dgame = FindGO<DungeonGame>("DungeonGame");
			dgame->ClearInGameMode();
			if (m_team == WIN) {
				if (IDungeonData().isFinalRound(m_dunNum)) {
					//ToNextStage();
					//MonsterDrop
					m_fadeFlag = true;
					m_fade->FadeOut();
					//ToMonsterDrop();
					//ToDungeonSelect();
				}
				else {
					ToNextRound();
				}
			}
			else {
				Lose();
			}
		}
	}
	if (m_fade->isFadeStop() && m_fadeFlag)
		ToMonsterDrop();
}

void DungeonResult::CameraUpdate() {
	if (m_cmove)
	{
		m_firstpos += m_addpos;
		m_firsttar += m_addtar;
		m_cam->SetPos(m_firstpos);
		m_cam->SetTar(m_firsttar);

		if ((m_firstpos - m_lastpos).Length() < 0.5f)
		{
			InitUI();
			m_BGM = NewGO<Sound>(0, "BGM");
			m_BGM->Init(L"Assets/sound/BGM/PerituneMaterial_OverWorld5_loop.wav", true);
			m_BGM->Play();
			m_cmove = false;
		}
	}
}

void DungeonResult::ToMonsterDrop() {
	IDungeonData().SetRound(0);
	auto md = NewGO<MonsterDrop>(0);
	md->setDungeonNum(m_dunNum);
	auto dGame = FindGO<DungeonGame>("DungeonGame");
	dGame->Relese();
	DeleteGO(this);
}