#include "stdafx.h"
#include "kikyo.h"

#include "../../GameData.h"

Kikyo::Kikyo()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/kikyo_chan/hero_taiki_animation.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/kikyo_chan/hero_walk_animation.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/kikyo_chan/kikyo_attack.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);
	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/kikyo_chan/kikyo_defe_f.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(false);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/kikyo_chan/kikyo_defe_m.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/kikyo_chan/kikyo_defe_e.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(false);

	SkinModelRender* sr = NewGO<SkinModelRender>(0, "smr");
	sr->Init(L"Assets/modelData/hero.cmo", m_anim, 6,enFbxUpAxisY);
	//sr->SetScale(CVector3::One() * 20);
	//sr->SetScale({ 1.8f,1.8f,1.8f });
	//sr->Init(L"Assets/modelData/uma.bone.cmo");
	sr->SetPosition(CVector3::Zero());

	MonsterInitParam prm;
	prm.HP = 50;
	prm.MP = 180;
	prm.DefencePow = 5;
	prm.ExDefensePow = 10;
	prm.AttackPow = 10;
	prm.ExAttackPow = 6;
	prm.Speed = 10;
	prm.Radius = 50;
	prm.Height = 150;
	prm.ModelRender = sr;
	prm.NumAnimation = 6;

	init(prm);

	m_ID = enKikyo;
	int cnt = 0;
	ActionID* ua = GameData::GetMonsterActions(m_ID, cnt);
	SetUseAction(ua, cnt);
}
