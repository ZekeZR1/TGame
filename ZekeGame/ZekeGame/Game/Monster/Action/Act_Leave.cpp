#include "stdafx.h"
#include "Act_Leave.h"
#include "../Monster.h"

Act_Leave::Act_Leave()
{
	m_ActionId = 2;
}

bool Act_Leave::Action(Monster * me)
{
	if (m_target == nullptr)
	{
		//me->Setiswalk(false);
		me->Setspeed(CVector3::Zero());
		me->anim_idle();
		return true;
	}
	CVector3 mepo = me->Getpos();
	CVector3 v = mepo - m_target->Getpos();
	CVector3 moveSpeed = m_target->Getspeed();

	//if (v.Length() > 1000)
	//{
	//	//me->Setiswalk(false);
	//	me->Setspeed(CVector3::Zero());
	//	me->anim_idle();
	//	return true;
	//}

	me->anim_walk();

	CVector3 vv = v;
	if (v.Length() < 700)
	{
		float cta = acosf(v.Dot(moveSpeed));
		float l = (mepo - m_old).Length();
		if (l < 0.05 && cta < 10)
		{
			if ((mepo.x * mepo.z) > 0)
			{
				CQuaternion rot;
				rot.SetRotationDeg(CVector3::Up(), 90);
				rot.Multiply(v);
			}
			else
			{
				CQuaternion rot;
				rot.SetRotationDeg(CVector3::Up(), 270);
				rot.Multiply(v);
			}
		}
	}
	/*CQuaternion rot;
	rot.SetRotationDeg(CVector3::Up(), 270);
	rot.Multiply(v);*/

	v.Normalize();
	v *= 25;
	me->Setspeed(v);
	me->Setiswalk(true);

	m_time += IGameTime().GetFrameDeltaTime();
	if (m_time > 5.0f)
	{
		me->Setspeed(CVector3::Zero());
		me->anim_idle();
		return true;
	}

	m_old = mepo;
	return false;
}
