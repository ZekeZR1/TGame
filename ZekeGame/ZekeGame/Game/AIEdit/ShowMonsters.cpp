#include "stdafx.h"
#include "ShowMonsters.h"
#include "../MonsterBox/MonsterBox.h"
#include "../GameCursor.h"
#include "..//GameData.h"
#include "ShowMonsterSkills.h"

bool ShowMonsters::Start() {
	m_cur = NewGO<GameCursor>(0);
	m_backSp = NewGO<SpriteRender>(0);
	m_backSp->Init(L"Assets/sprite/modesel_back.dds", 1000.f, 650.f);

	InitFont();
	InitButtons();
	return true;
}

void ShowMonsters::OnDestroy() {
	for (auto font : m_MonsterNames)
		DeleteGO(font);
	for (auto sp : m_frames)
		DeleteGO(sp);
	for (auto sp : m_monsterSps)
		DeleteGO(sp);
	DeleteGO(m_backSp);
}

void ShowMonsters::Update() {
	if (!m_isActive) return;
	ButtonUpdate();
}

void ShowMonsters::InitFont() {
	for (int i = 0; i < enNumMonster - 1; i++) {
		auto font = NewGO<FontRender>(1);
		font->SetTextType(CFont::en_Japanese);
		font->Init(m_MonsterNameList[i].c_str());
		m_MonsterNames.push_back(font);;
	}
}

void ShowMonsters::InitButtons() {
	static const float buttonDistX = 300;
	static const float buttonDistY = 200;
	CVector3 pos = m_basePos;
	for (int i = 0; i < m_MonsterNames.size(); i++) {
		if (i % 3 == 0) {
			pos.x = m_basePos.x;
			pos.y -= buttonDistY;
		}
		else {
			pos.x += buttonDistX;
		}
		auto path = GameData::GetMonsterIconPath(i+1);
		auto sp = NewGO<SpriteRender>(1);
		sp->Init(path, 150.f, 150.f);
		sp->SetPosition(pos);
		m_MonsterNames[i]->SetPosition({ pos.x + 50,pos.y });
		m_MonsterNames[i]->DrawShadow();
		m_monsterSps.push_back(sp);
		auto frame = NewGO<SpriteRender>(0);
		frame->Init(L"Assets/sprite/buttyon.dds", 300, 190, true);
		frame->SetPosition({ pos.x + 90,pos.y,pos.z });
		m_frames.push_back(frame);
	}
}

void ShowMonsters::ButtonUpdate() {
	for (auto i : m_frames) {
		i->SetCollisionTarget(m_cur->GetCursor());
		if (i->isCollidingTarget() and Mouse::isTrigger(enLeftClick)) {
			NewGO<ShowMonsterSkills > (0);
			m_isActive = false;
		}
	}
}