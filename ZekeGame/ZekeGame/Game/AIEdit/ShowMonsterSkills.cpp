#include "stdafx.h"
#include "ShowMonsterSkills.h"
#include "ShowMonsters.h"
#include "../GameCursor.h"

bool ShowMonsterSkills::Start() {
	m_backSp = NewGO<SpriteRender>(18);
	m_backSp->Init(L"Assets/sprite/menu.dds", 600, 720);

	m_quitSp = NewGO<SpriteRender>(25);
	m_quitSp->Init(L"Assets/sprite/deletepoint.dds", 50, 50,true,false);
	m_quitSp->SetPosition({ 280,330,0 });

	m_cur = FindGO<GameCursor>("cursor");


	LoadSkillInfo();

	static const int Ydist = 110;
	CVector3 pos = { -200, 250, 0 };
	for (int i = 0; i < 6 ; i++) {
		//�Z
		auto sp = NewGO<SpriteRender>(19);
		sp->Init(L"Assets/sprite/buttyon.dds", 150, 50);
		sp->SetPosition(pos);
		m_sps.push_back(sp);
		auto fr = NewGO<FontRender>(20);
		fr->SetTextType(CFont::en_Japanese);
		fr->Init(m_defSkillNamesStr[i].c_str(), { pos.x - 50,pos.y  + 25});
		fr->DrawShadow();
		m_defSkillNamesFR.push_back(fr);
		//�Z�ڍ׏��
		sp = NewGO<SpriteRender>(19);
		sp->Init(L"Assets/sprite/buttyon.dds", 350, 110);
		sp->SetPosition({ pos.x + 300,pos.y,pos.z });
		m_sps.push_back(sp);
		if (m_monsterSkillNameFR.size() > i)
			m_monsterSkillNameFR[i]->SetPosition({ pos.x + 250,pos.y + 50 });
		if (m_monsterSkillInfoFR.size()  > i)
			m_monsterSkillInfoFR[i]->SetPosition({ pos.x + 220,pos.y + 20 });
		
		pos.y -= Ydist;
	}
	return true;
}

void ShowMonsterSkills::OnDestroy() {
	for (auto sp : m_sps)
		DeleteGO(sp);
	for (auto fr : m_defSkillNamesFR)
		DeleteGO(fr);	
	for (auto fr : m_monsterSkillNameFR)
		DeleteGO(fr);	
	for (auto fr : m_monsterSkillInfoFR)
		DeleteGO(fr);
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

void ShowMonsterSkills::LoadSkillInfo() {
	int count;
	auto actions = GameData::GetMonsterActions(m_monsterId, count);
	for (int i = 0; i < count; i++) {
		auto name =GameData::GetActionName(actions[i]);
		auto fr = NewGO<FontRender>(20);
		fr->Init(name);
		fr->DrawShadow();
		fr->SetScale(0.4);
		m_monsterSkillNameFR.push_back(fr);

		fr = NewGO<FontRender>(20);
		fr->SetTextType(CFont::en_Japanese);
		auto info = GameData::GetActionInfo(actions[i]);
		fr->Init(info);
		fr->DrawShadow();
		fr->SetScale(0.8);
		m_monsterSkillInfoFR.push_back(fr);
	}
}