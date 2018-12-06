#include "stdafx.h"
#include "Act_Atack.h"

#include "../Monster.h"

bool Act_Atack::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;
	me->anim_atack();
	CVector3 v = m_target->Getpos() - me->Getpos();
	if (v.Length() < 100)
	{
		m_target->Damage(3);
		v.Normalize();
		v *= 50;
		m_target->StartKnockback(v);
	}
	return true;
}
