#include "stdafx.h"
#include "Act_Guardian.h"
#include "../../GameData.h"

Act_Guardian::Act_Guardian()
{
	m_ActionId = enGuardian;
}

bool Act_Guardian::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;

	if (m_first)
	{
		float mp = me->GetMP();
		if (mp < 10)
			return true;
		me->SetMP(mp - 10.0f);

		me->anim_defenseF();
		m_def = me->GetDefense();
		m_Exdef = me->GetExDefense();

		me->SetDefense(m_def * 3.f);
		me->SetExDefense(m_Exdef * 3.f);


		m_first = false;
	}
	else if (!me->isAnimPlay())
	{
		me->anim_defenseM();
		me->SetKnockback(CVector3::Zero());
	}
	if (m_time > 5)
	{
		me->SetDefense(m_def);
		me->SetExDefense(m_Exdef);
		me->anim_defenseE();
		return true;
	}

	for (auto mon : g_mons)
	{
		if (mon == me)
			continue;
		if (m_target == mon->Getactions()[0]->Gettarget())
		{
			mon->Getactions()[0]->Settarget(me);
		}
	}

	
	
	m_time += IGameTime().GetFrameDeltaTime();
	return false;
}
