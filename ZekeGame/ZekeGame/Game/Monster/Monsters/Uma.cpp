#include "stdafx.h"
#include "../Monster.h"
#include "Uma.h"

#include "../../GameData.h"

Uma::Uma()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/uma/anim_uma_idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/uma/anim_uma_walk.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/uma/anim_uma_atack.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/uma.cmo",m_anim,3);
	//sr->SetScale({ 1.8f,1.8f,1.8f });
	//sr->Init(L"Assets/modelData/uma.bone.cmo");
	sr->SetPosition(CVector3::Zero());
	
	MonsterInitParam prm;
	prm.HP = 100;
	prm.MP = 30;
	prm.DefencePow = 10;
	prm.ExDefensePow = 2;
	prm.AttackPow = 13;
	prm.ExAttackPow = 5;
	prm.Speed = 10;
	prm.Radius = 50;
	prm.Height = 250;
	prm.ModelRender = sr;
	prm.NumAnimation = 3;

	init(prm);

	m_ID = enUmataur;
	int cnt = 0;
	ActionID* ua = GameData::GetMonsterActions(m_ID, cnt);
	SetUseAction(ua, cnt);
}