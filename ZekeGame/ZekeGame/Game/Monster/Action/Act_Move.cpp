#include "stdafx.h"
#include "Act_Move.h"
#include "../../GameData.h"
Act_Move::Act_Move()
{
	m_ActionId = enMove;
}

bool Act_Move::Action(Monster* me)
{
	CVector3 mepo = me->Getpos();
	CVector3 v = mTarpos - mepo;
	if (v.Length() < 0.1f)
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
