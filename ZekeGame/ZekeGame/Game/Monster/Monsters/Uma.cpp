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
	//sr->Init(L"Assets/modelData/uma.bone.cmo");
	sr->SetPosition(CVector3::Zero());
	init
	(
		160,
		30,
		10,
		0,
		10,
		0,
		10,
		30,
		70,
		sr,
		3
	);
	//tginit(10, 10, 10, 20, 70, sr, 0);

	m_ID = 1;
}
