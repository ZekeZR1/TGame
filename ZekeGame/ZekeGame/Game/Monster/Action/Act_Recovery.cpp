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
		float mp = me->GetMP();
		if (mp < 20)
			return true;
		me->anim_extra1();
		
		float hp = m_target->GetHP();
		hp += 20;
		m_target->SetHP(hp);

		mp -= 20;
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
