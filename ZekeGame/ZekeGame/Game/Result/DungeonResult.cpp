#include "stdafx.h"
#include "../Game.h"
#include "../Dungeon/DungeonSelect.h"
#include "DungeonResult.h"

bool DungeonResult::Start() {
	m_resultSp = NewGO<SpriteRender>(0, "resultSp");
	if (m_team == 0) {
		m_resultSp->Init(L"Assets/Sprite/clear.dds", 500.f, 200.f);
	}
	else {
		m_resultSp->Init(L"Assets/Sprite/button1.dds", 500.f, 200.f);
	}

	return true;
}

void DungeonResult::OnDestroy() {
	DeleteGO(m_resultSp);
	DeleteGO(FindGO<Game>("Game"));

}

void DungeonResult::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		NewGO<DungeonSelect>(0, "dunSelect");
		DeleteGO(this);
	}
}