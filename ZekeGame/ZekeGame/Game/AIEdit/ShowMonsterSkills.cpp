#include "stdafx.h"
#include "ShowMonsterSkills.h"


bool ShowMonsterSkills::Start() {
	m_backSp = NewGO<SpriteRender>(3);
	m_backSp->Init(L"Assets/sprite/menu.dds", 600, 720);
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
	DeleteGO(m_backSp);
}

void ShowMonsterSkills::Update() {

}