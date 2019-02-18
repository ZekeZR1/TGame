#include "stdafx.h"
#include "Act_Defense.h"

#include "../../GameData.h"

Act_Defense::Act_Defense()
{
	m_ActionId = enDefense;
}


bool Act_Defense::Action(Monster * me)
{
	if (m_first)
	{
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
	m_time += IGameTime().GetFrameDeltaTime();
	return false;
}