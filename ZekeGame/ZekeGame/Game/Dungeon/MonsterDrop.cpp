#include "stdafx.h"
#include "../MonsterBox/MonsterBox.h"
#include "DungeonGame.h"
#include "../GameData.h"
#include "DungeonSelect.h"
#include "../GameCursor.h"
#include "DungeonData.h"
#include "MonsterDrop.h"
#include "../Fade/Fade.h"
#include <random>

MonsterDrop::MonsterDrop()
{
}


MonsterDrop::~MonsterDrop()
{
}


bool MonsterDrop::Start() {
	m_egg = NewGO<SkinModelRender>(0);
	m_egg->Init(L"Assets/modelData/egg.cmo");
	m_back = NewGO<SkinModelRender>(0);
	m_back->Init(L"Assets/modelData/dun_yuka.cmo");
	std::random_device rnd;
	auto drop = rnd() % 100;
	//if (drop >= 50) 
		//ToDungeonSelect();
	camera3d->SetPosition({ 0.f,300.f,600.f });
	camera3d->Update();
	m_monsterNameSp = NewGO<SpriteRender>(0);
	m_nextButtonSp = NewGO<SpriteRender>(0);
	m_nextButtonSp->Init(L"Assets/Sprite/button1.dds", 300.f, 100.f, true);
	m_nextButtonSp->SetPosition(m_nextButtonPos);
	m_cursor = NewGO<GameCursor>(0);
	m_monsterId = static_cast<MonsterID>(rnd() % enNumMonster);
	m_notifySp = NewGO<SpriteRender>(0);
	m_notifySp->Init(L"Assets/Sprite/notifyLine.dds", 650.f, 50.f);
	m_notifySp->SetPosition(m_notifyLinePos);
	m_notifyFont = NewGO<FontRender>(0);
	m_notifyFont->SetTextType(CFont::en_Japanese);
	IMonsterBox().GetMonster(m_monsterId);
	m_monster = NewGO<SkinModelRender>(0);
	switch (m_monsterId) {
	case enTest:
		//ToDungeonSelect();
		//m_monsterSp->Init(L"Assets/Sprite/fade_black.dds", 500.f, 500.f);
		//break;
	case enUmataur:
		m_animClip[0].Load(L"Assets/modelData/uma/anim_uma_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->Init(L"Assets/modelData/uma.cmo", m_animClip, 1);
		m_monsterNameSp->Init(L"Assets/Sprite/.dds",300.f,100.f);
		m_notifyFont->Init(L"”n‚¿‚á‚ñ‚ðƒQƒbƒg‚µ‚½‚æ", { m_notifyLinePos.x - 270.f,m_notifyLinePos.y + 15.f }, 0.f, CVector4::White, 1.f, { 1.f,1.f });
		break;
	case enFairy:
		m_animClip[0].Load(L"Assets/modelData/fairy/hnd_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->Init(L"Assets/modelData/hnd.cmo", m_animClip, 1);
		m_monsterNameSp->Init(L"Assets/Sprite/.dds", 300.f, 100.f);
		m_notifyFont->Init(L"—d¸‚¿‚á‚ñ‚ðƒQƒbƒg‚µ‚½‚æ", { m_notifyLinePos.x - 370.f,m_notifyLinePos.y + 15.f }, 0.f, CVector4::White, 1.f, { 1.f,1.f });

		break;
	}
	m_monster->PlayAnimation(0);
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	return true;
}

void MonsterDrop::OnDestroy() {
	DeleteGO(m_nextButtonSp);
	DeleteGO(m_notifySp);
	DeleteGO(m_monsterNameSp);
	DeleteGO(m_monster);
	DeleteGO(m_egg);
	DeleteGO(m_back);
	DeleteGO(m_cursor);
	DeleteGO(m_notifyFont);
}

void MonsterDrop::Update() {
	SceneTransition();
}



void MonsterDrop::ToDungeonSelect() {
	IDungeonData().SetRound(0);
	NewGO<DungeonSelect>(0);
	auto dGame = FindGO<DungeonGame>("DungeonGame");
	dGame->Relese();
	DeleteGO(this);
}

void MonsterDrop::SceneTransition() {
	m_nextButtonSp->SetCollisionTarget(m_cursor->GetCursor());
	if (m_nextButtonSp->isCollidingTarget()) {
		if (Mouse::isTrigger(enLeftClick)) {
			m_fadeFlag = true;
			m_fade->FadeOut();
		}
	}
	if (m_fade->isFadeStop() && m_fadeFlag) {
		ToDungeonSelect();
	}
}