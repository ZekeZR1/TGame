#include "stdafx.h"
#include "Act_Leave.h"
#include "../Monster.h"

bool Act_Leave::Action(Monster * me)
{
	if (m_target == nullptr)
	{
		//me->Setiswalk(false);
		me->Setspeed(CVector3::Zero());
		return true;
	}
	CVector3 v = me->Getpos() - m_target->Getpos();
	if (v.Length() > 1000)
	{
		//me->Setiswalk(false);
		me->Setspeed(CVector3::Zero());
		return true;
	}
	v.Normalize();
	v *= 25;
	me->Setspeed(v);
	me->Setiswalk(true);
	return false;
}
