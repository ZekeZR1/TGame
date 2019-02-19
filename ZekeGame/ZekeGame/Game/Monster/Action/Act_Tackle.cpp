#include "stdafx.h"
#include "Act_Tackle.h"
#include "../../GameData.h"
#include "../Monster.h"

Act_Tackle::Act_Tackle()
{
	m_ActionId = enTackle;
}

bool Act_Tackle::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;
	float mp = me->GetMP();
	if (ismp)
	{
		if(mp < 20)
			return true;
		ismp = false;
		me->SetMP(mp - 20);
		rush = m_target->Getpos() - me->Getpos();
		rush.Normalize();
		rush *= 200.0f;
		me->Setspeed(rush);
	}
	
	CVector3 mpos = me->Getpos();
	float mrad = me->Getradius() + 30;
	for (auto mon : g_mons)
	{
		if (mon == me)
			continue;
		if (mon == NULL)
			break;
		CVector3 epo = mon->Getpos();
		float len = (epo - mpos).Length();
		float mil = mon->Getradius() + mrad;
		if (len <= mil)
		{
			if (mon == m_target)
			{
				CVector3 knock = epo - mpos;
				knock.Normalize();
				knock *= 800;
				mon->StartKnockback(knock);

				float dam = 5.0f * me->GetAttack();
				mon->Damage(dam);
				me->Setspeed(CVector3::Zero());

				Sound* se = NewGO<Sound>(0, "snd");
				se->Init(L"Assets/sound/punch-high2.wav");
				se->Play();
				return true;
			}
			else
			{
				CVector3 knock = epo - mpos;
				knock.Normalize();
				knock *= 25;
				mon->StartKnockback(knock);

				float dam = 0.3f * me->GetAttack();
				mon->Damage(dam);

				Sound* se = NewGO<Sound>(0, "snd");
				se->Init(L"Assets/sound/punch-middle2.wav");
				se->Play();
			}
		}
	}
	if (m_time >= 2.1f)
	{
		me->Setspeed(CVector3::Zero());
		return true;
	}
	m_time += IGameTime().GetFrameDeltaTime();
	return false;
}
