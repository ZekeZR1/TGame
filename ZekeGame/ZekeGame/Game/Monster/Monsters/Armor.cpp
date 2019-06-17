#include "stdafx.h"
#include "Armor.h"
#include "../../GameData.h"

Armor::Armor()
{
	m_anim[en_idle].Load(L"Assets/modeldata/armor/armor_idle.tka");
	m_anim[en_idle].SetLoopFlag(true);
	m_anim[en_walk].Load(L"Assets/modeldata/armor/armor_walk.tka");
	m_anim[en_walk].SetLoopFlag(true);
	m_anim[en_atack].Load(L"Assets/modeldata/armor/armor_panch.tka");

	m_anim[en_defenseF].Load(L"Assets/modeldata/armor/armor_diffe_first.tka");
	m_anim[en_defenseM].Load(L"Assets/modeldata/armor/armor_diffe_mid.tka");
	m_anim[en_defenseM].SetLoopFlag(true);
	m_anim[en_defenseE].Load(L"Assets/modeldata/armor/armor_diffe_mid.tka");


	SkinModelRender* sr = NewGO<SkinModelRender>(0, "sr");
	sr->Init(L"Assets/modeldata/armor.cmo", m_anim, 6);
	sr->SetScale(CVector3::One() / 3.f);

	MonsterInitParam prm;
	prm.HP = 180;
	prm.MP = 60;
	prm.DefencePow = 100;
	prm.ExDefensePow = 0;
	prm.AttackPow = 40;
	prm.ExAttackPow = 0;
	prm.Speed = 30;
	prm.Radius = 10;
	prm.Height = 300;
	prm.ModelRender = sr;
	prm.NumAnimation = 6;

	init(prm);

	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enLeave;
	ua[enDefense] = enDefense;
	ua[4] = enTackle;
	ua[5] = enGuardian;
	SetUseAction(ua,6);

	m_ID = enArmor;
}
