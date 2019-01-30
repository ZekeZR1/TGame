#include "stdafx.h"
#include <memory>
#include <fstream>
#include "../Title/ModeSelect.h"
#include "../GameCursor.h"
#include "../StageSetup/StageSetup.h"
#include "DungeonAISelect.h"
#include "DungeonSelect.h"

DungeonSelect::DungeonSelect()
{
}


DungeonSelect::~DungeonSelect()
{
}


bool DungeonSelect::Start() {
	m_cur = NewGO<GameCursor>(2, "cur");

	CheckDungeonClearState();
	InitDungeonButtons();

	if (m_clearedDunNum != m_numDungeon - 1) {
		m_nextSp = NewGO<SpriteRender>(2);
		m_nextSp->Init(L"Assets/Sprite/nextDungeon.dds", 90.f, 30.f);
		bool isNext = false;
	}

	m_backSp = NewGO<SpriteRender>(0);
	m_backSp->Init(L"Assets/Sprite/button1.dds", 180.f, 60.f, true);
	CVector3 sPos = { -500.f, -270.f, 0.f };
	m_backSp->SetPosition(sPos);
	m_backTx = NewGO<FontRender>(0);
	CVector2 tPos;
	tPos.x = sPos.x;
	tPos.x += -45;
	tPos.y = sPos.y;
	tPos.y += 16.f;
	m_backTx->Init(L"戻る", tPos, 0.f, CVector4::White, 1.f, { 0.f,0.f });
	return true;
}

void DungeonSelect::OnDestroy() {
	for (auto sp : m_sps) {
		DeleteGO(sp);
	}
	for (auto font : m_fonts) {
		DeleteGO(font);
	}
	m_dungeonButton.clear();
	DeleteGO(m_cur);
	if (m_nextSp != nullptr) {
		DeleteGO(m_nextSp);
	}
	DeleteGO(m_backSp);
	DeleteGO(m_backTx);
}

void DungeonSelect::Update() {
	for (auto i : m_sps) {
		i->SetCollisionTarget(m_cur->GetCursor());
		if (Mouse::isTrigger(enLeftClick)) {
			if (i->isCollidingTarget()) {
				int dunNum = m_dungeonButton[i];
				if (dunNum > m_clearedDunNum + 1)
					return;
				auto dunAi = NewGO<DungeonAISelect>(0, "pvp");
				dunAi->SetDungeonNumber(dunNum);
				DeleteGO(this);
			}
		}
	}
	if (m_nextSp != nullptr) {
		CVector3 nextScale = CVector3::One();
		double sca = 1.f;
		sca = 1.f + sin(M_PI * 2 / 30 * count) * 0.03f;
		m_nextSp->SetScale(nextScale * sca);
		count++;
	}
	m_backSp->SetCollisionTarget(m_cur->GetCursor());
	if (Mouse::isTrigger(enLeftClick) && m_backSp->isCollidingTarget()) {
		NewGO<ModeSelect>(0, "modesel");
		DeleteGO(this);
	}
}

void DungeonSelect::CheckDungeonClearState() {
	{
		using namespace std;
		char outfile[] = "datafile.txt";
		ifstream fin(outfile, ios::in | ios::binary);
		if (!fin) {
			OutputDebugStringA("datafileのオープンに失敗しました");
			return;
		}
		int clearedDungeon;
		fin.read((char *)&clearedDungeon, sizeof(int));
		fin.close();
		if (clearedDungeon < 0 || clearedDungeon > 8) {
			clearedDungeon = -1;
			ofstream fout;
			fout.open("datafile.txt", ios::out | ios::binary | ios::trunc);
			fout.write((char*)&clearedDungeon, sizeof(int));
			fout.close();
			OutputDebugStringA("ダンジョンのクリアデータが謎い\n");
			char message[256];
			sprintf_s(message, "%d\n", clearedDungeon);
			OutputDebugStringA(message);
		}
		m_clearedDunNum = clearedDungeon;
	}
}


void DungeonSelect::InitDungeonButtons() {
	CVector3  pos = CVector3::Zero();
	pos.y += 280.f;
	for (int i = 0; i < m_numDungeon; i++) {
		//init sprite
		m_sps.push_back(NewGO<SpriteRender>(0, "sp"));
		m_sps[i]->Init(L"Assets/Sprite/DadandanBk.dds", SPRITE_W, SPRITE_H, true);
		m_sps[i]->SetPosition(pos);
		//init text
		m_fonts.push_back(NewGO<FontRender>(1, "font"));
		wchar_t dungeon[256];
		swprintf_s(dungeon, L"ダンジョン%d", i + 1);
		CVector4 fontCol;
		if (i == m_clearedDunNum + 1) {
			CVector3 m_nextDunPos = pos;
			m_nextDunPos.x += 150.f;
			m_nextDunPos.y += 25.f;
			m_nextSp->SetPosition(m_nextDunPos);
		}
		if (i > m_clearedDunNum + 1) {
			fontCol = m_notYetClearCol;
		}
		else {
			fontCol = m_ClearCol;
		}
		m_fonts[i]->Init(dungeon, { pos.x + m_toFixMisalignment.x,pos.y + m_toFixMisalignment.y }, 0.f, fontCol, 1.f, m_fPivot);
		//down position
		pos.y -= m_spaceToNextSprite;
		//map
		m_dungeonButton[m_sps[i]] = i;
	}
}