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

bool Act_Atack::Chase(Monster* me)
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

bool Act_Atack::Attack(Monster* me)
{
	if (m_isfirst)
	{
		me->anim_atack();
		CVector3 v = m_target->Getpos() - me->Getpos();
		if (v.Length() < me->Getradius() + m_target->Getradius() + 10)
		{
			float dm = 1.5 * me->GetAttack();
			m_target->Damage(dm);
			v.Normalize();
			v *= 50;
			m_target->StartKnockback(v);
			s = NewGO<Sound>(0, "snd");
			s->Init(L"Assets/sound/kick-low1.wav", false);
			s->Play();

			/*CEffect* effe = NewGO<CEffect>(0, "effe");
			effe->Play(L"Assets/effect/panti/panti.efk");
			effe->SetPosition(m_target->Getpos());
			CQuaternion rot = me->GetRotation();
			effe->SetRotation(rot);
			effe->SetScale({ 3,3,3 });*/
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
