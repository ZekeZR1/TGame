#include "stdafx.h"
#include "RedHead.h"

#include "../../GameData.h"

RedHead::RedHead()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/RedHead/idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/RedHead/run.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/RedHead/RedHead_tyoppu.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);
	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/RedHead/RedHead_defe_f.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(false);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/RedHead/RedHead_defe_m.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/RedHead/RedHead_defe_e.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(false);
	m_anim[Monster::en_extra1].Load(L"Assets/modelData/RedHead/RedHead_Zoi.tka");
	m_anim[Monster::en_extra1].SetLoopFlag(false);
	m_anim[Monster::en_extra2].Load(L"Assets/modelData/RedHead/clear.tka");
	m_anim[Monster::en_extra2].SetLoopFlag(false);

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/RedHead.cmo", m_anim, 8);
	//sr->SetScale(CVector3::One() * 20);
	sr->SetPosition(CVector3::Zero());
	init
	(
		//160,
		80,
		30,
		10,
		0,
		10,
		0,
		10,
		50,
		150,
		sr,
		8
	);
	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enLeave;
	ua[enDefense] = enDefense;
	ua[4] = enTackle;
	ua[5] = enGuardian;
	SetUseAction(ua, 6);
	//tginit(10, 10, 10, 20, 70, sr, 0);

	m_ID = enRedHead;
}
