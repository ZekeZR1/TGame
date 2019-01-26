#include "stdafx.h"
#include "../Game.h"
#include "../Dungeon/DungeonSelect.h"
#include "ResultCamera.h"
#include "../GameCursor.h"
#include "DungeonResult.h"

bool DungeonResult::Start() {
	assert(m_dunNum != -1);
	m_resultSp = NewGO<SpriteRender>(0, "resultSp");
	m_buttonSp = NewGO<SpriteRender>(0, "next");
	m_buttonSp->Init(L"Assets/Sprite/button1.dds", 300.f, 100.f, true);
	m_buttonSp->SetPosition(m_buttonPos);
	m_buttonText = NewGO<FontRender>(0);
	CVector3 textpos = m_buttonPos;
	textpos.y += 15.f;
	textpos.x += -30.f;
	m_buttonText->Init(L"OK", { textpos.x,textpos.y }, 0.f, CVector4::White, 1.f, { 0.5f,0.5f });
	if (m_team == 0) {
		m_resultSp->Init(L"Assets/Sprite/win.dds", 500.f, 200.f, true);
		//TODO : ダンジョンクリアセーブとかモンスタードロップとかできるようにする
	}
	else {
		m_resultSp->Init(L"Assets/Sprite/lose.dds", 500.f, 200.f, true);
	}
	m_cursor = NewGO<GameCursor>(0);
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
			NewGO<DungeonSelect>(0);
			DeleteGO(this);
		}
	}
}