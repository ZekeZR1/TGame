#include "stdafx.h"
#include "Act_Chase.h"
//#include "MonsterAction.h"
#include "../Monster.h"

bool Act_Chase::Action(Monster* me)
{
	if (m_target == nullptr)
	{
		me->Setspeed(CVector3::Zero());
		//me->Setiswalk(false);
		return true;
	}

	CVector3 v = m_target->Getpos() - me->Getpos();
	if (v.Length() < 30+m_target->Getradius())
	{
		me->Setspeed(CVector3::Zero());
		//me->Setiswalk(false);
		return true;
	}
	v.Normalize();
	v *= 15;
	me->Setspeed(v);
	me->Setiswalk(true);
	return false;
}
