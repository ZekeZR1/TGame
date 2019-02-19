#include "stdafx.h"
#include "../Game.h"
#include "../Dungeon/DungeonSelect.h"
#include "ResultCamera.h"
#include "../GameCursor.h"
#include  <fstream>
#include "DungeonResult.h"
#include "../Dungeon/DungeonData.h"
#include "../Dungeon/DungeonTransition.h"
#include "../Dungeon/DungeonGame.h"

bool DungeonResult::Start() {
	InitUI();
	return true;
}

void DungeonResult::OnDestroy() {
	DeleteGO(m_resultSp);
	DeleteGO(FindGO<Game>("Game"));
	DeleteGO(m_buttonSp);
	DeleteGO(m_buttonText);
	DeleteGO(m_cursor);
}

void DungeonResult::Update() {
	m_buttonSp->SetCollisionTarget(m_cursor->GetCursor());
	if (Mouse::isTrigger(enLeftClick)) {
		if (m_buttonSp->isCollidingTarget()) {
			SaveDungeonClearState();
			auto dgame = FindGO<DungeonGame>("DungeonGame");
			dgame->ClearInGameMode();
			if (m_team == WIN) {
				if (IDungeonData().isFinalRound(m_dunNum)) {
					//ToNextStage();
					ToDungeonSelect();
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
}

void DungeonResult::SaveDungeonClearState(){
	{
		using namespace std;
		char outfile[] = "datafile.txt";
		ifstream fin(outfile, ios::in | ios::binary);
		if (!fin) {
			OutputDebugStringA("datafileÇÃÉIÅ[ÉvÉìÇ…é∏îsÇµÇ‹ÇµÇΩ");
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
			fout.open("datafile.txt", ios::out | ios::binary | ios::trunc);
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
		m_resultSp->Init(L"Assets/Sprite/win.dds", 500.f, 200.f, true);
	}
	else {
		m_resultSp->Init(L"Assets/Sprite/lose.dds", 500.f, 200.f, true);
	}
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