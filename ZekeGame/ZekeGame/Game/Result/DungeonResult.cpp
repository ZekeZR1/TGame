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
	m_fade->FadeIn();
	return true;
}

void DungeonResult::OnDestroy() {
	DeleteGO(m_srteam);
	DeleteGO(FindGO<Game>("Game"));
	DeleteGO(m_srwin);
	DeleteGO(m_nextfont);
	DeleteGO(m_cam);
}

void DungeonResult::Update() {
	ButtonUpdate();
	CameraUpdate();
}

void DungeonResult::SaveDungeonClearState() {
	//負けたらセーブデータをいじる必要はない
	if (m_team != WIN) return;
	//最終ラウンドで勝利したら次のステージを開放する
	if (IDungeonData().isFinalRound(m_dunNum)) {
		using namespace std;
		int currentNum = IDungeonData().GetDungeonNum();
		ofstream fout;
		char ms0[256];
		int cleared = currentNum + 1;
		fout.open("Assets/saveData/clearstate.dd", ios::out | ios::binary | ios::trunc);
		fout.write((char*)& cleared, sizeof(int));
		fout.close();
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
	m_nextfont = NewGO<FontRender>(5, "fr");
	m_nextfont->SetTextType(CFont::en_Japanese);
	m_nextfont->Init(L"クリックしてください", { -600,-300 }, 0, { 1,1,1,1 }, 1, { 0,0 });
	m_nextfont->DrawShadow();

	m_srwin = NewGO<SpriteRender>(0, "sr");
	//m_srwin->Init(L"Assets/sprite/win.dds", 462, 262);
	m_srwin->SetPivot({ 0,0.5f });
	m_srwin->SetPosition({ -610,210,0 });

	m_srteam = NewGO<SpriteRender>(0, "sr");
	if (m_team == WIN)
	{
		//m_srteam->Init(L"Assets/sprite/redteamp.dds", 768.0f, 315.75f);
		m_srteam->Init(L"Assets/sprite/res_redteam.dds", 768.0f * 1.5f, 212.21f * 1.5f);
		m_srwin->Init(L"Assets/sprite/res_Win.dds", 462 * 1.1f, 183.256f * 1.1f);
	}
	else
	{
		//m_srteam->Init(L"Assets/sprite/blueteamp.dds", 795.75f, 315.75f);
		m_srteam->Init(L"Assets/sprite/res_redteam.dds", 795.75f * 1.5f, 212.21f * 1.5f);
		m_srwin->Init(L"Assets/sprite/res_Lose.dds", 462 * 1.1f, 183.256f * 1.1f);
	}
	m_srteam->SetPivot({ 0,0.5f });
	m_srteam->SetPosition({ -620,-210,0 });
	//m_resultSp = NewGO<SpriteRender>(0, "resultSp");
	//m_buttonSp = NewGO<SpriteRender>(0, "next");
	//m_buttonSp->Init(L"Assets/Sprite/button1.dds", 300.f, 100.f, true);
	//m_buttonSp->SetPosition(m_buttonPos);
	//m_buttonText = NewGO<FontRender>(0);
	//CVector3 textpos = m_buttonPos;
	//textpos.y += 15.f;
	//textpos.x += -30.f;
	//m_buttonText->Init(L"OK", { textpos.x,textpos.y }, 0.f, CVector4::White, 1.f, { 0.5f,0.5f });

	//if (m_team == WIN) {
	//	m_resultSp->Init(L"Assets/Sprite/res_win.dds", 500.f, 200.f, true);
	//}
	//else {
	//	m_resultSp->Init(L"Assets/Sprite/res_lose.dds", 500.f, 200.f, true);
	//}
	////m_resultSp->SetPosition({ -410,160,0 });
	//m_resultSp->SetPosition({ -410,60,0 });

	////m_cursor = NewGO<GameCursor>(0);
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

	float hie = g_mons[0]->Getheight();
	m_lastpos = { hie / -13 + hie / -5, hie / 2 + hie / 7.3f, hie / 10 + hie / 4 };
	m_lasttar = { 15, hie / 2 + hie / 7.f, 0 };

	m_addpos = (m_lastpos - m_firstpos) / 8.0f;
	m_addtar = (m_lasttar - m_firsttar) / 8.0f;
}

void DungeonResult::ButtonUpdate() {
	//if (m_buttonSp == nullptr)
	//	return;
	//m_buttonSp->SetCollisionTarget(m_cursor->GetCursor());
	if (Mouse::isTrigger(enLeftClick)) {
		auto se = NewGO<Sound>(0);
		se->Init(L"Assets/sound/se/button.wav", false);
		se->Play();
		//if (m_buttonSp->isCollidingTarget()) {
		SaveDungeonClearState();
		auto dgame = FindGO<DungeonGame>("DungeonGame");
		dgame->ClearInGameMode();
		m_fadeFlag = true;
		m_fade->FadeOut();
				
	}
	if (m_fade->isFadeStop() && m_fadeFlag)
	{
		if (m_team == WIN) {
			if (IDungeonData().isFinalRound(m_dunNum)) {
				ToMonsterDrop();
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