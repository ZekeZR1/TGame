#include "stdafx.h"
#include "VisualScriptAI.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterActionManeger.h"
#include "../GameData.h"

VisualScriptAI::VisualScriptAI()
{
}

VisualScriptAI::~VisualScriptAI()
{
}

void VisualScriptAI::Run()
{
	for (auto vsLine : m_vsLines)
	{
		Monster* tarmon = nullptr;
		bool isPASS = false;
		Target old = tNone;
		for (auto vsOrder : vsLine)
		{
			switch (vsOrder.what)
			{
			case hp:
				isPASS = whatHP(vsOrder.target, vsOrder.bl, vsOrder.num, tarmon,old);
				break;
			case mp:
				isPASS = whatMP(vsOrder.target, vsOrder.bl, vsOrder.num, tarmon, old);
				break;
			case state:
				isPASS = whatState(vsOrder.target, vsOrder.state, tarmon, old);
				break;
			case action:
				isPASS = false;
				if (tarmon == nullptr)
				{
					whatAction(vsOrder.target, vsOrder.action);
				}
				else
				{
					whatAction(tarmon, vsOrder.action);
				}
				break;
			}
			if (!isPASS)
				break;
			old = vsOrder.target;
		}
		
	}
}

bool VisualScriptAI::whatHP(Target target, BL bl, Num num, Monster *& mon, Target old)
{
	bool res = false;
	Monster* vmon = nullptr;
	int team = m_me->Getteam();
	float left = 0;
	float right = 0;


	switch (num)
	{
	case n1:
		right = 0.01f;
		break;
	case n10:
		right = 0.1f;
		break;
	case n30:
		right = 0.3f;
		break;
	case n50:
		right = 0.5f;
		break;
	case n70:
		right = 0.7f;
		break;
	case n90:
		right = 0.9f;
		break;
	case n100:
		right = 1.0f;
		break;
	}

	if (target == old)
	{
		left = mon->GetHP() / mon->GetMaxHP();
		if (bl == little)
		{
			float v = left;
			left = right;
			right = v;
		}

		if (left > right)
		{
			res = true;
		}
	}
	else if (target == me)
	{
		left = m_me->GetHP() / m_me->GetMaxHP();
		if (bl == little)
		{
			float v = left;
			left = right;
			right = v;
		}

		if (left > right)
		{
			vmon = m_me;
			res = true;
		}
	}
	else
	{
		//enemyの場合はチームナンバーを反転させる
		if (target != buddy)
		{
			if (team == 0)
			{
				team = 1;
			}
			else
			{
				team = 0;
			}
		}

		for (auto m : g_mons)
		{
			if (m == nullptr)
				break;
			if (m->Getteam() == team)
			{
				float vleft = m->GetHP() / m->GetMaxHP();
				float vright = right;

				//littleの場合は右左を入れ替える。
				if (bl == little)
				{
					float v = vleft;
					vleft = vright;
					vright = v;
				}

				if (vleft > vright)
				{
					vmon = m;
					res = true;
					break;
				}
				else
				{
					res = false;
				}
			}
		}
	}
	if (mon == nullptr)
	{
		mon = vmon;
	}
	return res;
}

bool VisualScriptAI::whatMP(Target target, BL bl, Num num, Monster *& mon, Target old)
{
	bool res = false;
	Monster* vmon = nullptr;
	int team = m_me->Getteam();
	float left = 0;
	float right = 0;


	switch (num)
	{
	case n1:
		right = 0.01f;
		break;
	case n10:
		right = 0.1f;
		break;
	case n30:
		right = 0.3f;
		break;
	case n50:
		right = 0.5f;
		break;
	case n70:
		right = 0.7f;
		break;
	case n90:
		right = 0.9f;
		break;
	case n100:
		right = 1.0f;
		break;
	}

	if (target == old)
	{
		left = mon->GetMP() / mon->GetMaxMP();
		if (bl == little)
		{
			float v = left;
			left = right;
			right = v;
		}

		if (left > right)
		{
			res = true;
		}
	}
	else if (target == me)
	{
		left = m_me->GetMP() / m_me->GetMaxMP();
		if (bl == little)
		{
			float v = left;
			left = right;
			right = v;
		}

		if (left > right)
		{
			vmon = m_me;
			res = true;
		}
	}
	else
	{
		//enemyの場合はチームナンバーを反転させる
		if (target != buddy)
		{
			if (team == 0)
			{
				team = 1;
			}
			else
			{
				team = 0;
			}
		}

		for (auto m : g_mons)
		{
			if (m == nullptr)
				break;
			if (m->Getteam() == team)
			{
				float vleft = m->GetMP() / m->GetMaxMP();
				float vright = right;

				//littleの場合は右左を入れ替える。
				if (bl == little)
				{
					float v = vleft;
					vleft = vright;
					vright = v;
				}

				if (vleft > vright)
				{
					vmon = m;
					res = true;
					break;
				}
				else
				{
					res = false;
				}
			}
		}
	}
	if (mon == nullptr)
	{
		mon = vmon;
	}
	return res;
}

bool VisualScriptAI::whatState(Target target, State state, Monster *& mon, Target old)
{
	int team;
	Monster* tarmon = nullptr;
	if (target == me)
	{
		tarmon = m_me;
	}
	else
	{
		if (target == buddy)
		{
			team = m_me->Getteam();
		}
		else
		{
			team = m_me->Getteam() == 0 ? 1 : 0;
		}
		for (auto mon : g_mons)
		{
			if (mon == nullptr)
				break;
			if (team == mon->Getteam())
			{
				tarmon = mon;
			}
		}
	}
	mon = tarmon;
	return true;
}

void VisualScriptAI::whatAction(Target target, Action action)
{
	int team;
	Monster* tarmon = nullptr;
	if (target == me)
	{
		tarmon = m_me;
	}
	else
	{
		if (target == buddy)
		{
			team = m_me->Getteam();
		}
		else
		{
			team = m_me->Getteam() == 0 ? 1 : 0;
		}
		for (auto mon : g_mons)
		{
			if (mon == nullptr)
				break;
			if (team == mon->Getteam())
			{
				tarmon = mon;
			}
		}
	}
	ActionID* ua = m_me->GetUseAction();
	switch (action)
	{
	case attack:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enAtack], tarmon->Getnum()));
		break;
	case leave:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enLeave], tarmon->Getnum()));
		break;
	case chase:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enChase], tarmon->Getnum()));
		break;
	case defence:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enDefense], tarmon->Getnum()));
		break;
	case recovery:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enRecovery], tarmon->Getnum()));
		break;
	case ex1:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[4], tarmon->Getnum()));
		break;
	case ex2:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[5], tarmon->Getnum()));
		break;
	}
}

void VisualScriptAI::whatAction(Monster * target, Action action)
{

	ActionID* ua = m_me->GetUseAction();
	switch (action)
	{
	case attack:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enAtack], target->Getnum()));
		break;
	case leave:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enLeave], target->Getnum()));
		break;
	case chase:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enChase], target->Getnum()));
		break;
	case defence:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[enDefense], target->Getnum()));
		break;
	case recovery:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[5], target->Getnum()));
		break;
	case ex1:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[4], target->Getnum()));
		break;
	case ex2:
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[5], target->Getnum()));
		break;
	}
}
