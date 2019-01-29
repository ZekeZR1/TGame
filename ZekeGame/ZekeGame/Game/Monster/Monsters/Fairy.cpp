#include "stdafx.h"
#include "../Monster.h"
#include "Fairy.h"


Fairy::Fairy()
{
	m_anim[Monster::en_idle].Load(L"Assets/modelData/fairy/hnd_idle.tka");
	m_anim[Monster::en_idle].SetLoopFlag(true);
	m_anim[Monster::en_walk].Load(L"Assets/modelData/fairy/hnd_idle.tka");
	m_anim[Monster::en_walk].SetLoopFlag(true);
	m_anim[Monster::en_atack].Load(L"Assets/modelData/fairy/hnd_atack.tka");
	m_anim[Monster::en_atack].SetLoopFlag(false);


	SkinModelRender* smr = NewGO<SkinModelRender>(0, "smr");
	smr->Init(L"Assets/modelData/hnd.cmo",m_anim,3);
	init(10, 30, 30, 20, 70, smr,3);
}
