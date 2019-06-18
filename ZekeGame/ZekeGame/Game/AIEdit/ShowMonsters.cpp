#include "stdafx.h"
#include "ShowMonsters.h"
#include "AIEditNodeSelectButtons.h"
#include "AIEditNodeMenu.h"
#include "../MonsterBox/MonsterBox.h"
#include "../GameCursor.h"
#include "..//GameData.h"
#include "ShowMonsterSkills.h"


bool ShowMonsters::Start() {
	m_cur = FindGO<GameCursor>("cursor");

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
	DeleteGO(m_quitSp);
	DeleteGO(m_leftSp);
	DeleteGO(m_rightSp);
}

void ShowMonsters::Update() {
	if (!m_isActive) return;
	ButtonUpdate();
}

void ShowMonsters::InitSideButtons() {
	CVector3 pos = { 400.f,-300.f,0.f };
	m_leftSp = NewGO<SpriteRender>(3);
	m_leftSp->Init(L"Assets/Sprite/leftButton.dds", 50.f, 100.f, true);
	m_leftSp->SetPosition({ -400.f, -300.f, 0.f });
	m_rightSp = NewGO<SpriteRender>(3);
	m_rightSp->Init(L"Assets/Sprite/rightButton.dds", 50.f, 100.f, true);
	m_rightSp->SetPosition(pos);
}

void ShowMonsters::InitFont() {
	for (int i = 1; i < enNumMonster; i++) {
		auto font = NewGO<FontRender>(1);
		font->SetTextType(CFont::en_Japanese);
		font->Init(GameData::GetMonsterName(static_cast<MonsterID>(i)));
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
		}if (i % nButtonMax == 0 and i != 0) {
			pos.y = m_basePos.y;
			pos.x += 1500.f;
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

	m_quitSp = NewGO<SpriteRender>(4);
	m_quitSp->Init(L"Assets/Sprite/deletepoint.dds", 100, 50);
	m_quitSp->SetPosition({ 0,-300,0 });

	m_totalPage = (static_cast<int>(enNumMonster)  - 1)  / nButtonMax;
	InitSideButtons();
}

void ShowMonsters::ButtonUpdate() {
	//モンスターのスキルを表示する
	for (auto i : m_frames) {
		i->SetCollisionTarget(m_cur->GetCursor());
		if (i->isCollidingTarget() and Mouse::isTrigger(enLeftClick)) {
			NewGO<ShowMonsterSkills > (0);
			m_isActive = false;
		}
	}
	//閉じる
	m_quitSp->SetCollisionTarget(m_cur->GetCursor());
	if (m_quitSp->isCollidingTarget() and Mouse::isTrigger(enLeftClick)) {
		auto aieditnodeselectbuttons = FindGO<AIEditNodeSelectButtons>("selectbuttons");
		aieditnodeselectbuttons->Setmenuselect(false);
		DeleteGO(this);
	}

	ChangePage();

}

void ShowMonsters::ChangePage() {
	m_leftSp->SetCollisionTarget(m_cur->GetCursor());
	m_rightSp->SetCollisionTarget(m_cur->GetCursor());
	static const int moveParam = 1500;
	//前のページ
	if (m_leftSp->isCollidingTarget() and Mouse::isTrigger(enLeftClick)) {
		if (m_currentPage == 1) return;
		m_currentPage--;
		for (auto sp : m_monsterSps) {
			auto pos = sp->GetPosition();
			pos.x += moveParam;
			sp->SetPosition(pos);
		}
		for (auto sp : m_frames) {
			auto pos = sp->GetPosition();
			pos.x += moveParam;
			sp->SetPosition(pos);
		}
		for (auto font : m_MonsterNames) {
			auto pos = font->GetPosition();
			pos.x += moveParam;
			font->SetPosition(pos);
		}
	}
	//次のページ
	if (m_rightSp->isCollidingTarget() and Mouse::isTrigger(enLeftClick)) {
		if (m_currentPage == m_totalPage) return;
		m_currentPage++;
		for (auto sp : m_monsterSps) {
			auto pos = sp->GetPosition();
			pos.x -= moveParam;
			sp->SetPosition(pos);
		}
		for (auto sp : m_frames) {
			auto pos = sp->GetPosition();
			pos.x -= moveParam;
			sp->SetPosition(pos);
		}
		for (auto font : m_MonsterNames) {
			auto pos = font->GetPosition();
			pos.x -= moveParam;
			font->SetPosition(pos);
		}
	}
}