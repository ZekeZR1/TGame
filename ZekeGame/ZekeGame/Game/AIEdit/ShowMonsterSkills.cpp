#include "stdafx.h"
#include "ShowMonsterSkills.h"
#include "ShowMonsters.h"
#include "../GameCursor.h"

bool ShowMonsterSkills::Start() {
	m_backSp = NewGO<SpriteRender>(3);
	m_backSp->Init(L"Assets/sprite/menu.dds", 600, 720);

	m_quitSp = NewGO<SpriteRender>(10);
	m_quitSp->Init(L"Assets/sprite/deletepoint.dds", 50, 50,true,false);
	m_quitSp->SetPosition({ 280,330,0 });

	m_cur = FindGO<GameCursor>("cursor");

	static const int Ydist = 110;
	CVector3 pos = { -200, 250, 0 };
	for (int i = 0; i < 6 ; i++) {
		auto sp = NewGO<SpriteRender>(4);
		sp->Init(L"Assets/sprite/buttyon.dds", 150, 50);
		sp->SetPosition(pos);
		m_sps.push_back(sp);
		sp = NewGO<SpriteRender>(4);
		sp->Init(L"Assets/sprite/buttyon.dds", 350, 110);
		sp->SetPosition({ pos.x + 300,pos.y,pos.z });
		m_sps.push_back(sp);
		pos.y -= Ydist;
	}
	return true;
}

void ShowMonsterSkills::OnDestroy() {
	for (auto sp : m_sps)
		DeleteGO(sp);
	DeleteGO(m_backSp);
	DeleteGO(m_quitSp);
}

void ShowMonsterSkills::Update() {
	m_quitSp->SetCollisionTarget(m_cur->GetCursor());
	if (m_quitSp->isCollidingTarget() and Mouse::isTrigger(enLeftClick)) {
		auto smc = FindGO<ShowMonsters>("MonstersInfo");
		smc->SetWindowActive(true);
		DeleteGO(this);
	}
}