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
	init
	(
		160,
		30,
		5,
		15,
		5,
		10,
		30,
		20,
		70,
		smr,
		7
	);
	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enLeave;
	ua[enDefense] = enDefense;
	ua[4] = enFire;
	ua[5] = enActNone;
	SetUseAction(ua);

	m_ID = enFairy;
}
