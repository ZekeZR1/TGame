#include "stdafx.h"
#include "../Monster.h"
#include "Fairy.h"
#include "../../GameData.h"


Fairy::Fairy()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/fairy/hnd_idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/fairy/hnd_idle.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/fairy/hnd_atack.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);

	m_anim[Monster::en_defenseF].Load(L"Assets/modelData/fairy/hnd_defenseFirst.tka");
	m_anim[Monster::en_defenseF].SetLoopFlag(false);
	m_anim[Monster::en_defenseM].Load(L"Assets/modelData/fairy/hnd_defenseMid.tka");
	m_anim[Monster::en_defenseM].SetLoopFlag(true);
	m_anim[Monster::en_defenseE].Load(L"Assets/modelData/fairy/hnd_defenseEnd.tka");
	m_anim[Monster::en_defenseE].SetLoopFlag(false);

	m_anim[Monster::en_extra1].Load(L"Assets/modelData/fairy/hnd_ex1.tka");
	m_anim[Monster::en_extra1].SetLoopFlag(false);


	SkinModelRender* smr = NewGO<SkinModelRender>(0, "smr");
	
	smr->Init(L"Assets/modelData/hnd.cmo",m_anim,7);
	//smr->SetScale({ 1.8f,1.8f,1.8f });

	MonsterInitParam prm;
	prm.HP = 60;
	prm.MP = 30;
	prm.DefencePow = 5;
	prm.ExDefensePow = 15;
	prm.AttackPow = 5;
	prm.ExAttackPow = 10;
	prm.Speed = 30;
	prm.Radius = 20;
	prm.Height = 130;
	prm.ModelRender = smr;
	prm.NumAnimation = 7;

	init(prm);

	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enLeave;
	ua[enDefense] = enDefense;
	ua[4] = enFire;
	ua[5] = enActNone;
	SetUseAction(ua,6);

	m_ID = enFairy;
}
