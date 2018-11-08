#include "stdafx.h"
#include "TestAction.h"
//#include "MonsterAction.h"
#include "Monster.h"

bool tesAction::Action()
{
	Monster* mon;
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		if (obj->Getnum() == m_targetNum)
		{
			mon = obj;
			return false;
		}
		return true;
	});

	return false;
}
