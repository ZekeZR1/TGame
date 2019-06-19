#include "stdafx.h"
#include "Shell.h"

#include "../../GameData.h"

Shell::Shell()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/shell/hotate_idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/shell/hotate_idle.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/shell/hotate_attack.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);
	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/shell/hotate_defe_f.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(false);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/shell/hotate_defe_m.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/shell/hotate_defe_e.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(false);

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/hotate.cmo", m_anim, 6);
	sr->SetScale(CVector3::One()*2);
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
	prm.Height = 300;
	prm.ModelRender = sr;
	prm.NumAnimation = 6;

	init(prm);

	m_ID = enChris;
	int cnt = 0;
	
	ActionID* ua = GameData::GetMonsterActions(m_ID, cnt);
	SetUseAction(ua, cnt);
	//tginit(10, 10, 10, 20, 70, sr, 0);

	
}
