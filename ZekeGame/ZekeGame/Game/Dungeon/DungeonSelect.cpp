#include "stdafx.h"
#include <memory>
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

	for (int i = 0; i < m_numDungeon; i++) {
		//init sprite
		m_sps.push_back(NewGO<SpriteRender>(0, "sp"));
		m_sps[i]->Init(L"Assets/Sprite/DadandanBk.dds", SPRITE_W, SPRITE_H, true);
		m_sps[i]->SetPosition(pos);
		//init text
		m_fonts.push_back(NewGO<FontRender>(1, "font"));
		wchar_t dungeon[256];
		swprintf_s(dungeon, L"ƒ_ƒ“ƒWƒ‡ƒ“%d", i + 1);
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
}

void DungeonSelect::Update() {
	for (auto i : m_sps) {
		i->SetCollisionTarget(m_cur->GetCursor());
		if (Mouse::isTrigger(enLeftClick)) {
			if (i->isCollidingTarget()) {
				auto dunAi = NewGO<DungeonAISelect>(0, "DungeonAISelect");
				int dunNum = m_dungeonButton[i];
				dunAi->SetDungeonNumber(dunNum);
				DeleteGO(this);
			}
		}
	}
}