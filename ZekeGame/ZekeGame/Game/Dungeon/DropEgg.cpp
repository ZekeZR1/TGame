#include "stdafx.h"
#include "../MonsterBox/MonsterBox.h"
#include "DungeonGame.h"
#include "../GameData.h"
#include "DungeonSelect.h"
#include "../GameCursor.h"
#include "DungeonData.h"
#include "MonsterDrop.h"
#include <random>
#include "DropEgg.h"
#include "../Monster/Monsters/Armor.h"
#include "../Monster/Monsters/Book.h"
#include"..//Monster/Monsters/Uma.h"
#include "../Monster/Monsters/Fairy.h"
#include "../Monster/Monsters/Goblin.h"

DropEgg::DropEgg()
{
}


DropEgg::~DropEgg()
{
	
}


bool DropEgg::Start() {
	m_egg = NewGO<SkinModelRender>(0);
	m_egg->SetShadowReciever(false);
	m_egg->SetDirLight({ 0, 0, -1, 0 }, 0);
	m_egg->Init(L"Assets/modelData/egg.cmo", nullptr, 0, enFbxUpAxisY);
	m_egg->SetPosition(m_eggPos);
	std::random_device rnd;
	m_monsterId = static_cast<MonsterID>(rnd() % enNumMonster);
	IMonsterBox().GetMonster(m_monsterId);
	auto se = NewGO<Sound>(0);
	se->Init(L"Assets/sound/dungeon/puyon1.wav", false);
	se->Play();
	return true;
}

void DropEgg::OnDestroy() {
	DeleteGO(m_monster);
	DeleteGO(m_egg);
}

void DropEgg::Update() {
	static float fixTiming = 5.f;
	static float bigTiming = 5.f + fixTiming;
	static float smallTiming = 5.9f + fixTiming;
	static float effectTiming = 4.7f + fixTiming;
	static float bkEffectTiming = 15.f + fixTiming;
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
		auto se = NewGO<Sound>(0);
		se->Init(L"Assets/sound/dungeon/light.wav", false);
		se->Play();
	}
	if (m_timer >= bkEffectTiming && !m_isPlayedBackEffect) {
	/*	ef = NewGO<CEffect>(0, "DRB");
		ef->SetScale(CVector3::One() * 10);
		CQuaternion rot = CQuaternion::Identity();
		ef->SetRotation(rot);
		auto p = m_monsterPos;
		p.z -= 10.f;
		p.y += 100.f;
		ef->SetPosition(p);
		ef->Play(L"Assets/effect/drback.efk");
		m_efk->Play(L"Assets/effect/dropefk.efk", 2.5f);*/
		ef = NewGO<CEffect>(0, "DRB");
		//m_efk->SetScale({ 8.f,8.f,8.f });
		ef->SetScale({ 13.f,13.f,13.f });
		auto p = m_monsterPos;
		p.z -= 10.f;
		p.y += 200.f;
		//m_efk->SetPosition({ 0.f,0.f,-200.f });
		ef->SetPosition(p);
		ef->Play(L"Assets/effect/drback.efk");
		m_isPlayedBackEffect = true;
	}
	//new monster
	if (m_timer >= monsterTiming && !m_isDisplayMonster) {
		NewMonster();
		m_isDisplayMonster = true;
	}
}

void DropEgg::NewMonster() {
	m_monster = NewGO<SkinModelRender>(1);
	m_monster->SetPosition(m_monsterPos);
	m_monster->SetScale(CVector3::One() * 2);
	m_monster->SetDirLight({ 0, 0, -1, 0}, 0);
	auto se = NewGO<Sound>(0);
	//se->Init(L"Assets/sound/dungeon/ban1.wav", false);
	se->Init(L"Assets/sound/dungeon/newmon.wav", false);
	se->Play();
	{
		auto se = NewGO<Sound>(0);
		//se->Init(L"Assets/sound/dungeon/ban1.wav", false);
		se->Init(L"Assets/sound/dungeon/newmon1.wav", false);
		se->Play();
	}
	switch (m_monsterId) {
	case enTest:
		//ToDungeonSelect();
		//m_monsterSp->Init(L"Assets/Sprite/fade_black.dds", 500.f, 500.f);
		//break;
	case enUmataur:
		m_animClip[0].Load(L"Assets/modelData/uma/anim_uma_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->Init(L"Assets/modelData/uma.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"馬");
		m_monster->PlayAnimation(0);
		break;
	case enFairy:
		m_animClip[0].Load(L"Assets/modelData/fairy/hnd_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->Init(L"Assets/modelData/hnd.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"妖精");
		m_monster->PlayAnimation(0);
		break;
	case enArmor:
		m_animClip[0].Load(L"Assets/modelData/armor/armor_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->SetScale(m_modelScale * 0.3);
		m_monster->Init(L"Assets/modelData/armor.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"アーマー");
		m_monster->PlayAnimation(0);
		break;
	case enBook:
		m_animClip[0].Load(L"Assets/modelData/book/book_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->Init(L"Assets/modelData/book.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"本");
		m_monster->PlayAnimation(0);
		break;
	case enGoblin:
		m_animClip[0].Load(L"Assets/modelData/gob/gob_idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->SetScale(m_modelScale * 30);
		m_monster->Init(L"Assets/modelData/gob.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"ゴブリン");
		m_monster->PlayAnimation(0);
		break;
	case enRedHead:
		m_animClip[0].Load(L"Assets/modelData/RedHead/idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->SetScale(m_modelScale * 30);
		m_monster->Init(L"Assets/modelData/RedHead.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"レッドヘッド");
		m_monster->PlayAnimation(0);
		break;
	case enKikyo:
		m_animClip[0].Load(L"Assets/modelData/kikyo_chan/hero_taiki_animation.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->SetScale(m_modelScale * 30);
		m_monster->Init(L"Assets/modelData/hero.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"キキョウちゃん");
		m_monster->PlayAnimation(0);
		break;
	case enShikoChu:
		//m_animClip[0].Load(L"Assets/modelData/si_bug/si_bug.tka");
		//m_animClip[0].SetLoopFlag(true);
		m_monster->SetScale(m_modelScale * 30);
		m_monster->Init(L"Assets/modelData/si_bug.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"死光虫");
		break;
	case enRingo:
		m_animClip[0].Load(L"Assets/modelData/RingoChan/idle.tka");
		m_animClip[0].SetLoopFlag(true);
		m_monster->SetScale(m_modelScale * 30);
		m_monster->Init(L"Assets/modelData/ringo.cmo", m_animClip, 1);
		wcscpy(m_monsterName, L"りんごちゃん");
		m_monster->PlayAnimation(0);
		break;
	}
}