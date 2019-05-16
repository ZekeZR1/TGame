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
	init(
		180,
		60,
		100,
		0,
		40,
		0,
		30,
		10,
		30,
		sr,
		6
	);

	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enLeave;
	ua[enDefense] = enDefense;
	ua[4] = enActNone;
	ua[5] = enActNone;
	SetUseAction(ua);

	m_ID = enArmor;
}
