#include "stdafx.h"
#include "Act_Recovery.h"

#include "../../GameData.h"

Act_Recovery::Act_Recovery()
{
	m_ActionId = enRecovery;
}

bool Act_Recovery::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;
	if (m_first)
	{
		float CMP = 5.f;
		float mp = me->GetMP();
		if (mp < CMP)
			return true;
		me->anim_extra1();
		
		float hp = m_target->GetHP();
		hp += 20;
		m_target->SetHP(hp);

		mp -= CMP;
		me->SetMP(mp);

		m_first = false;
	}
	else
	{
		if (!me->isAnimPlay())
		{
			return true;
		}
	}
	return false;
}
