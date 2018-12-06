#include "stdafx.h"
#include "Act_Leave.h"
#include "../Monster.h"

bool Act_Leave::Action(Monster * me)
{
	if (m_target == nullptr)
	{
		//me->Setiswalk(false);
		me->Setspeed(CVector3::Zero());
		me->anim_idle();
		return true;
	}
	CVector3 v = me->Getpos() - m_target->Getpos();
	if (v.Length() > 1000)
	{
		//me->Setiswalk(false);
		me->Setspeed(CVector3::Zero());
		me->anim_idle();
		return true;
	}
	me->anim_walk();
	v.Normalize();
	v *= 25;
	me->Setspeed(v);
	me->Setiswalk(true);

	m_time += IGameTime().GetFrameDeltaTime();
	if (m_time > 15.0f)
	{
		me->Setspeed(CVector3::Zero());
		me->anim_idle();
		return true;
	}

	return false;
}
