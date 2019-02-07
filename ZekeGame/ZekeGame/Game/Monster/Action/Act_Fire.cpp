#include "stdafx.h"
#include "Act_Fire.h"
#include "../MonsterAction.h"

#include "../Monster.h"
#include "../../GameData.h"

Act_Fire::Act_Fire()
{
	m_effect = NewGO<CEffect>(0, "eff");
	m_ActionId = enFire;
}

bool Act_Fire::Action(Monster * me)
{
	if (!m_isPlayAnim)
	{
		me->anim_extra1();
	}
	if (!m_effect->IsPlay() && !m_isPlayAnim)
	{
		float mp = me->GetMP();
		if (mp < 20)
			return true;
		mp -= 20;
		me->SetMP(mp);

		m_pos = m_target->Getpos();

		CVector3 sc = CVector3::One();
		sc *= 5;
		m_effect->SetScale(sc);
		m_effect->SetPosition(m_pos);
		m_effect->Play(L"Assets/effect/fire1/fire1.efk");
		
		m_isPlayAnim = true;
	}
	if (m_effect->IsPlay())
	{
		for (auto mon : g_mons)
		{
			if (mon == NULL)
				break;
			CVector3 len = m_pos - mon->Getpos();
			if (len.Length() < 30)
			{
				mon->DamageEx(me->GetExAttack());
			}
		}
	}
	else if (!m_effect->IsPlay() && m_isPlayAnim)
	{
		me->anim_idle();
		return true;
	}
	return false;
}
