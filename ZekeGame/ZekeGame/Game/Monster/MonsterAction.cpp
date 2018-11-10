#include "stdafx.h"
#include "MonsterAction.h"
#include "Monster.h"

void MonsterAction::Settarget(int num)
{
	QueryGOs<Monster>("monster", [&](Monster* obj)->bool
	{
		if (obj->Getnum() == num)
		{
			m_target = obj;
		}
		return true;
	});
}
