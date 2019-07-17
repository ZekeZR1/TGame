#include "stdafx.h"
#include "Act_specialAttack.h"
#include "../../GameData.h"

Act_SpecialAttack::Act_SpecialAttack()
{
	m_ActionId = enSpecialAttack;
}

bool Act_SpecialAttack::Action(Monster* me)
{
	if (m_target == nullptr)
		return true;

	bool res = false;
	switch (m_state)
	{
	case enSChase:
	{
		bool ench = false;
		ench = Chase(me);
		if (ench)
			m_state = enSAttack;
	}
	break;
	case enSAttack:
		res = Attack(me);
		break;
	}
	return res;
}

bool Act_SpecialAttack::Chase(Monster* me)
{
	CVector3 mepo = me->Getpos();
	CVector3 v = m_target->Getpos() - mepo;
	if (v.Length() < m_target->Getradius() + me->Getradius() + 1)
	{
		me->Setspeed(CVector3::Zero());
		//me->Setiswalk(false);
		me->anim_idle();
		return true;
	}
	me->anim_walk();
	v.Normalize();


	v *= 15;
	me->Setspeed(v);
	me->Setiswalk(true);

	m_time += IGameTime().GetFrameDeltaTime();
	if (m_time > 10.0f)
	{
		me->Setspeed(CVector3::Zero());
		me->anim_idle();
		return true;
	}

	return false;
}

bool Act_SpecialAttack::Attack(Monster* me)
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
			CVector3 pos = mon->Getpos() - mpos;
			if (pos.Length() < mradi + mon->Getradius() + 50)
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
