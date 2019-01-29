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
	CVector3  pos = CVector3::Zero();
	pos.y += 250.f;
	CheckDungeonClearState();
	for (int i = 0; i < m_numDungeon; i++) {
		//init sprite
		m_sps.push_back(NewGO<SpriteRender>(0, "sp"));
		m_sps[i]->Init(L"Assets/Sprite/DadandanBk.dds", SPRITE_W, SPRITE_H, true);
		m_sps[i]->SetPosition(pos);
		//init text
		m_fonts.push_back(NewGO<FontRender>(1, "font"));
		wchar_t dungeon[256];
		swprintf_s(dungeon, L"ダンジョン%d", i + 1);
		m_fonts[i]->Init(dungeon, { pos.x + m_toFixMisalignment.x,pos.y + m_toFixMisalignment .y}, 0.f, m_fDefCol, 1.f, m_fPivot);
		//down position
		pos.y -= m_spaceToNextSprite;
		//map
		m_dungeonButton[m_sps[i]] = i;
	}
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
		//ステージ選択制限
	}
}
