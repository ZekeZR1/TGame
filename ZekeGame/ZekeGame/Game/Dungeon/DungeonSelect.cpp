#include "stdafx.h"
#include <memory>
#include "../Title/ModeSelect.h"
#include "../GameCursor.h"
#include "DungeonSelect.h"

DungeonSelect::DungeonSelect()
{
}


DungeonSelect::~DungeonSelect()
{
}


bool DungeonSelect::Start() {
	m_cur = NewGO<GameCursor>(1, "cur");

	CVector3  pos = CVector3::Zero();
	pos.y += 200.f;
	for (int i = 0; i < 8; i++) {
		m_sps.push_back(NewGO<SpriteRender>(0, "sp"));
		m_sps[i]->Init(L"Assets/Sprite/DungeonSp.dds", 400.f, 90.f, true);
		m_sps[i]->SetPosition(pos);
		pos.y -= 100.f;
	}
	return true;
}

void DungeonSelect::OnDestroy() {
	for (auto i : m_sps) {
		DeleteGO(i);
	}
}

void DungeonSelect::Update() {
	for (auto i : m_sps) {
		i->SetCollisionTarget(m_cur->GetCursor());
		if (Mouse::isTrigger(enLeftClick)) {
			if (i->isCollidingTarget()) {
				i->Init(L"Assets/Sprite/DungeonSpS.dds", 500.f, 100.f, true);
			}
		}
	}
	if (g_pad[0].IsTrigger(enButtonA)) {
		for (auto i : m_sps) {
			i->Init(L"Assets/Sprite/DungeonSp.dds", 500.f, 100.f);
		}
	}
}