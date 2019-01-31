#include "stdafx.h"
#include "Act_Atack.h"

#include "../Monster.h"

Act_Atack::Act_Atack()
{
	m_ActionId = 1;
}

bool Act_Atack::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;
	me->anim_atack();
	CVector3 v = m_target->Getpos() - me->Getpos();
	if (v.Length() < me->Getradius() + m_target->Getradius() + 10)
	{
		float dm = 3 * me->GetAttack() - m_target->GetDefense();
		dm += 3;
		m_target->Damage(dm);
		v.Normalize();
		v *= 50;
		m_target->StartKnockback(v);
	}
	return true;
}
