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
	std::random_device rnd;
	auto drop = rnd() % 100;
	//if (drop >= 50) 
		//ToDungeonSelect();
	camera3d->SetPosition({ 0.f,100.f,450.f });
	camera3d->Update();
	InitUI();
	InitModels();
	m_monsterId = static_cast<MonsterID>(rnd() % enNumMonster);
	IMonsterBox().GetMonster(m_monsterId);
	//NewMonster();
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
	EggPfm();
	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<MonsterDrop>(0);
	}
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

void MonsterDrop::NewMonster() {
	m_monster = NewGO<SkinModelRender>(0);
	m_notifySp = NewGO<SpriteRender>(0);
	m_notifySp->Init(L"Assets/Sprite/notifyLine.dds", 650.f, 50.f);
	m_notifySp->SetPosition(m_notifyLinePos);
	switch (m_monsterId) {
	case enTest:
		//ToDungeonSelect();
		//m_monsterSp->Init(L"Assets/Sprite/fade_black.dds", 500.f, 500.f);
		//break;
	case enUmataur:
		m_animClip[0].Load(L"Assets/modelData/uma/anim_uma_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->Init(L"Assets/modelData/uma.cmo", m_animClip, 1);
		//m_monsterNameSp->Init(L"Assets/Sprite/.dds", 300.f, 100.f);
		m_notifyFont->Init(L"”n‚¿‚á‚ñ‚ðƒQƒbƒg‚µ‚½‚æ", { m_notifyLinePos.x - 270.f,m_notifyLinePos.y + 15.f }, 0.f, CVector4::White, 1.f, { 1.f,1.f });
		break;
	case enFairy:
		m_animClip[0].Load(L"Assets/modelData/fairy/hnd_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->Init(L"Assets/modelData/hnd.cmo", m_animClip, 1);
		//m_monsterNameSp->Init(L"Assets/Sprite/.dds", 300.f, 100.f);
		m_notifyFont->Init(L"—d¸‚¿‚á‚ñ‚ðƒQƒbƒg‚µ‚½‚æ", { m_notifyLinePos.x - 370.f,m_notifyLinePos.y + 15.f }, 0.f, CVector4::White, 1.f, { 1.f,1.f });
		break;
	}
	m_monster->PlayAnimation(0);
	m_monster->SetPosition(m_monsterPos);
}

void MonsterDrop::InitUI() {
	m_cursor = NewGO<GameCursor>(0);
	//m_monsterNameSp = NewGO<SpriteRender>(0);
	m_nextButtonSp = NewGO<SpriteRender>(0);
	m_nextButtonSp->Init(L"Assets/Sprite/button1.dds", 300.f, 100.f, true);
	m_nextButtonSp->SetPosition(m_nextButtonPos);
	m_notifyFont = NewGO<FontRender>(1);
	m_notifyFont->SetTextType(CFont::en_Japanese);
}

void MonsterDrop::InitModels() {
	m_egg = NewGO<SkinModelRender>(0);
	m_egg->Init(L"Assets/modelData/egg.cmo", nullptr, 0, enFbxUpAxisY);
	m_back = NewGO<SkinModelRender>(0);
	m_back->Init(L"Assets/modelData/dropwall.cmo");
	m_back->SetPosition(m_backPosition);
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotationDeg(CVector3::AxisX(), 90.f);
	m_back->SetRotation(rot);
}

void MonsterDrop::EggPfm() {
	if (m_egg == nullptr)
		return;
	CVector3 eggMove = CVector3::Zero();
	m_eggPos += eggMove;
	if (m_timer <= 2.f) {
		m_timer += 0.15f;
	}
	else {
		m_timer = 0.f;
		m_eggnum++;
	}
	float ease = EASE::InOutQuad(4.f, -2.f, 2.f, m_timer);
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotationDeg(CVector3::AxisZ(), ease * m_eggnum);
	m_eggRot.Multiply(rot);
	m_egg->SetPosition(m_eggPos);
	m_egg->SetRotation(m_eggRot);
	if (m_eggnum == 5.f) {
		if (!mb_efk) {
			m_efk = NewGO<CEffect>(0);
			m_efk->SetScale({ 6.f,6.f,6.f });
			m_efk->Play(L"Assets/effect/dropefk.efk", 2.5f);
			mb_efk = true;
		}
	}
	if (m_eggnum >= 5) {
		//big
		float eggsize = 1.2f;
		if (mf_eggSca >= eggsize) {
			mflag_eggbig = false;
		}
		if (mf_eggSca <= eggsize && mflag_eggbig) {
			mf_eggSca += 0.1f;
		}
		if(mf_eggSca >= 0.0f && !mflag_eggbig)
			mf_eggSca -= 0.1f;
		m_eggSca *= mf_eggSca;
		m_egg->SetScale(m_eggSca);
	}
	if (m_eggnum == 14.f) {
		DeleteGO(m_egg);
		m_egg = nullptr;
		NewMonster();
	}
}