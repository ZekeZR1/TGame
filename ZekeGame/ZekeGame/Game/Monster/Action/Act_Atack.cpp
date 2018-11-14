#include "stdafx.h"
#include "Act_Atack.h"

#include "../Monster.h"

bool Act_Atack::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;
	
	CVector3 v = m_target->Getpos() - me->Getpos();
	if (v.Length() < 100)
	{
		m_target->Damage(3);
	}
	return true;
}
