#include "stdafx.h"
#include "MonsterActionManeger.h"
#include "MonsterAction.h"

#include "TestAction.h"

MonsterAction * MonsterActionManeger::LoadAction(int id,int target)
{
	switch (id)
	{
	case test:
		tesAction* ac = NewGO<tesAction>(0, "action");
		ac->Settarget(target);
		return ac;
		break;
	}
	return nullptr;
}
