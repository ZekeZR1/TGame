#include "stdafx.h"
#include "Goblin.h"

#include "../../GameData.h"

Goblin::Goblin()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/gob/gob_idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/gob/gob_walk.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/gob/gob_panch.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);
	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/gob/gob_dife_F.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(false);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/gob/gob_dife_M.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/gob/gob_dife_M.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(false);

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/gob.cmo", m_anim, 3);
	sr->SetScale(CVector3::One() * 20);
	//sr->SetScale({ 1.8f,1.8f,1.8f });
	//sr->Init(L"Assets/modelData/uma.bone.cmo");
	sr->SetPosition(CVector3::Zero());
		
	MonsterInitParam prm;
	prm.HP = 80;
	prm.MP = 30;
	prm.DefencePow = 10;
	prm.ExDefensePow = 0;
	prm.AttackPow = 10;
	prm.ExAttackPow = 0;
	prm.Speed = 10;
	prm.Radius = 50;
	prm.Height = 150;
	prm.ModelRender = sr;
	prm.NumAnimation = 3;

	init(prm);

	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enLeave;
	ua[enDefense] = enDefense;
	ua[4] = enTackle;
	ua[5] = enGuardian;
	SetUseAction(ua, 6);
	//tginit(10, 10, 10, 20, 70, sr, 0);

	m_ID = enGoblin;
}
