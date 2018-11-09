#include "stdafx.h"
#include "TestAction.h"
//#include "MonsterAction.h"
#include "Monster.h"

bool tesAction::Action()
{
	CVector3 v = m_target->Getpos() - m_me->Getpos();
	if (v.Length() < 50)
		return true;

	v.Normalize();
	v *= 50;
	m_me->Setspeed(v);
	return false;
}
