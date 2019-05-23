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
		250,
		sr,
		3
	);
	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enActNone;
	ua[enDefense] = enDefense;
	ua[4] = enTackle;
	ua[5] = enGuardian;
	SetUseAction(ua,6);
	//tginit(10, 10, 10, 20, 70, sr, 0);

	m_ID = enUmataur;
}
