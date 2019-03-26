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
	camera3d->SetPosition({ 0.f,0.f,450.f });
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
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
#if _DEBUG
	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<MonsterDrop>(0);
	}
#endif
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
	m_monster->SetScale(m_modelScale);
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
	m_egg->SetPosition(m_eggPos);
	m_back = NewGO<SkinModelRender>(0);
	m_back->Init(L"Assets/modelData/dropwall.cmo");
	m_back->SetPosition(m_backPosition);
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotationDeg(CVector3::AxisX(), 90.f);
	m_back->SetRotation(rot);
}

void MonsterDrop::EggPfm() {
	static float fixTiming = 5.f;
	static float bigTiming = 5.f + fixTiming;
	static float smallTiming = 5.9f + fixTiming;
	static float effectTiming = 4.7f + fixTiming;
	static float monsterTiming = 20.f + fixTiming;
	static float bigSpeed = 0.01f;
	static float smallSpeed = 0.05f;
	static float rotationParam = 10.f;
	static float rotationSpeed = 0.2f;
	if (m_egg == nullptr)
		return;
	m_timer += 0.1f;

	//rotation
	m_eggTime += rotationSpeed;
	float x = sin(m_eggTime);
	m_eggRot.SetRotationDeg(CVector3::AxisZ(), x * rotationParam);
	m_egg->SetRotation(m_eggRot);
	//scale
	if (m_timer >= bigTiming && m_timer <= smallTiming) {
		mf_eggSca += bigSpeed;
	}
	if (m_timer >= smallTiming && mf_eggSca >= 0.f) {
		mf_eggSca -= smallSpeed;
	}
	m_eggSca *= mf_eggSca;
	m_egg->SetScale(m_eggSca);
	//effect
	if (m_timer >= effectTiming && !m_isPlayedEffect) {
		m_efk = NewGO<CEffect>(0);
		//m_efk->SetScale({ 8.f,8.f,8.f });
		m_efk->SetScale({ 9.f,9.f,9.f });
		m_efk->SetPosition({ 0.f,-50.f,200.f });
		m_efk->Play(L"Assets/effect/dropefk.efk", 2.5f);
		m_isPlayedEffect = true;
	}
	//new monster
	if (m_timer >= monsterTiming && !m_isDisplayMonster) {
		NewMonster();
		m_isDisplayMonster = true;
	}
}