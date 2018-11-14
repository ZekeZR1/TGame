#include "stdafx.h"
#include "MonsterActionManeger.h"
#include "MonsterAction.h"

#include "Action/Act_Chase.h"
#include "Action/Act_Atack.h"

MonsterAction * MonsterActionManeger::LoadAction(int id,int target)
{
	MonsterAction* ac;
	switch (id)
	{
	case en_Chase:
		ac = NewGO<Act_Chase>(0, "action");
		ac->Settarget(target);
		return ac;
		break;
	case en_Atack:
		ac = NewGO<Act_Atack>(0, "action");
		ac->Settarget(target);
		return ac;
		break;
	}
	return nullptr;
}
