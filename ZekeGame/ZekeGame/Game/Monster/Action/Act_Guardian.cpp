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
		float CMP = 10;
		float mp = me->GetMP();
		if (mp < CMP)
			return true;
		me->SetMP(mp - CMP);

		me->anim_defenseF();
		m_def = me->GetDefense();
		m_Exdef = me->GetExDefense();

		float magnification = 1.2f;
		me->SetDefense(m_def * magnification);
		me->SetExDefense(m_Exdef * magnification);


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
		if (mon == nullptr)
			break;

		//printf("load start\n");



		if (mon == me || mon->Getactions().size() == 0 || mon->Getteam() == me->Getteam())
		{
			//printf("load end\n");
			continue;
			
		}
		if (mon->Getactions()[0]->Gettarget() == NULL)
		{
			//printf("load end\n");
			continue;
		}
		if (mon->Getactions()[0]->Gettarget()->Getteam() != me->Getteam())
		{
			//printf("load end\n");
			continue;
		}
		//printf("mon:%d\n", mon->Getactions()[0]->Gettarget()->Getnum());
		//printf("load end\n");
		/*if (m_target == mon->Getactions()[0]->Gettarget())
		{*/
		mon->Getactions()[0]->Settarget(me);
		//}
	}

	
	
	m_time += IGameTime().GetFrameDeltaTime();
	return false;
}
