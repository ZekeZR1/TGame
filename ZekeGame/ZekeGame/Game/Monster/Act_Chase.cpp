#include "stdafx.h"
#include "Act_Chase.h"
//#include "MonsterAction.h"
#include "Monster.h"

bool Act_Chase::Action(Monster* me)
{
	CVector3 v = m_target->Getpos() - me->Getpos();
	if (v.Length() < 50)
	{
		me->Setspeed(CVector3::Zero());
		return true;
	}
	v.Normalize();
	v *= 5;
	me->Setspeed(v);
	return false;
}
