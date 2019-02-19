#include "stdafx.h"
#include "Act_Atack.h"

#include "../Monster.h"
#include "../../GameData.h"

Act_Atack::Act_Atack()
{
	m_ActionId = enAtack;
}

bool Act_Atack::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;
	if (m_isfirst)
	{
		me->anim_atack();
		CVector3 v = m_target->Getpos() - me->Getpos();
		if (v.Length() < me->Getradius() + m_target->Getradius() + 10)
		{
			float dm = 3 * me->GetAttack();
			m_target->Damage(dm);
			v.Normalize();
			v *= 50;
			m_target->StartKnockback(v);
			s = NewGO<Sound>(0, "snd");
			s->Init(L"Assets/sound/kick-low1.wav", false);
			s->Play();
		}
		m_isfirst = false;
	}
	else if (!me->isAnimPlay())
	{
		me->anim_idle();
		return true;
	}
	
	return false;
}
