#include "stdafx.h"
#include "VisualScriptAI.h"
#include "../Monster/Monster.h"
#include "../Monster/MonsterActionManeger.h"
#include "../GameData.h"

VisualScriptAI::VisualScriptAI(Monster* me, std::string* path)
{
	m_me = me;

	FILE* f = fopen(path->c_str(), "rb");

	if (f == NULL)
	{
		VisualScriptLine line;
		line.reserve(1);
		line.push_back(VisualScriptOrder());
		m_vsLines.reserve(1);
		m_vsLines.push_back(line);
		return;
	}

	char head[6];
	fread(head, 6, 1, f);
	int col = 0;
	fread(&col, 1, 1, f);

	for (int L = 0; L < 8; L++)
	{
		VisualScriptLine vsl;
		for (int D = 0; D < 3; D++)
		{
			VisualScriptOrder vso;
			for (int P = 0; P < 6; P++)
			{
				int R = 0;
				fread(&R, 2, 1, f);
				switch (P)
				{
				case 0:
					vso.target = (Target)R;
					break;
				case 1:
					vso.what = (What)R;
					break;
				case 2:
					vso.bl = (BL)R;
					break;
				case 3:
					vso.num = (Num)R;
					break;
				case 4:
					vso.state = (State)R;
					break;
				case 5:
					vso.action = (Action)R;
					break;
				}
				
			}
			vsl.push_back(vso);
		}
		m_vsLines.push_back(vsl);
	}

	fclose(f);
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
					//tarmon の中にちゃんと入っていても、テクニックのターゲットとtarmonが一致しなかった場合があるのでその処理
					switch(vsOrder.target)
					{
					case me:
						if(tarmon == m_me)
							whatAction(tarmon, vsOrder.action);
						else
							whatAction(vsOrder.target, vsOrder.action);
						break;
					case buddy:
						if (tarmon->Getteam() == m_me->Getteam())
							whatAction(tarmon, vsOrder.action);
						else
							whatAction(vsOrder.target, vsOrder.action);
						break;
					case enemy:
						if (tarmon->Getteam() != m_me->Getteam())
							whatAction(tarmon, vsOrder.action);
						else
							whatAction(vsOrder.target, vsOrder.action);
						break;
					}
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
	if (tarmon == nullptr)
		return;
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
		m_me->AddAction(MonsterActionManeger::LoadAction(ua[4], tarmon->Getnum()));
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
