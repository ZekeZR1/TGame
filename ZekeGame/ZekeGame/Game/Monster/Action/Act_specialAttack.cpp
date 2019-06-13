#include "stdafx.h"
#include "Act_specialAttack.h"
#include "../../GameData.h"

Act_SpecialAttack::Act_SpecialAttack()
{
	m_ActionId = enSpecialAttack;
}

bool Act_SpecialAttack::Action(Monster* me)
{
	if (m_isFirst)
	{
		m_ef = NewGO<CEffect>(0, "ef");
		m_ef->SetPosition(me->Getpos());
		m_ef->Play(L"Assets/effect/SpecialAttack.efk");
		m_ef->SetScale(CVector3::One() * 4);
		
		m_isFirst = false;
	}
	if (m_ef->IsPlay())
	{
		CVector3 mpos = me->Getpos();
		float mradi = me->Getradius();
		for (auto mon : g_mons)
		{
			if (mon == nullptr)
				break;
			CVector3 pos = mon->Getpos()-mpos;
			if (pos.Length() < mradi+mon->Getradius()+50)
			{
				float dam = me->GetExAttack();
				if (mon == me)
				{
					dam /= 2;
				}
				mon->DamageEx(dam);
			}
		}
	}
	else
	{

		DeleteGO(m_ef);
		
		return true;
	}
	return false;
}
