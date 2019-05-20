#include "stdafx.h"
#include "MonsterActionManeger.h"
#include "MonsterAction.h"
#include "../GameData.h"

#include "Action/Act_Chase.h"
#include "Action/Act_Atack.h"
#include "Action/Act_Leave.h"
#include "Action/Act_Defense.h"
#include "Action/Act_Fire.h"
#include "Action/Act_Tackle.h"
#include "Action/Act_Guardian.h"
#include "Action/Act_Recovery.h"
#include "Action/Act_superBeam.h"
#include "Action/Act_ObstMove.h"
#include "Action/Act_Cleanse.h"

MonsterAction * MonsterActionManeger::LoadAction(int id,int target)
{
	MonsterAction* ac;
	switch (id)
	{
	case enChase:
		ac = NewGO<Act_Chase>(0, "action");
		ac->Settarget(target);
		return ac;
		break;
	case enAtack:
		ac = NewGO<Act_Atack>(0, "action");
		ac->Settarget(target);
		return ac;
		break;
	case enLeave:
		ac = NewGO<Act_Leave>(0, "action");
		ac->Settarget(target);
		return ac;
		break;
	case enDefense:
		ac = NewGO<Act_Defense>(0, "action");
		ac->Settarget(target);
		return ac;

	case enFire:
		ac = NewGO<Act_Fire>(0, "action");
		ac->Settarget(target);
		return ac;
	case enTackle:
		ac = NewGO<Act_Tackle>(0, "action");
		ac->Settarget(target);
		return ac;
	case enGuardian:
		ac = NewGO<Act_Guardian>(0, "action");
		ac->Settarget(target);
		return ac;
	case enRecovery:
		ac = NewGO<Act_Recovery>(0, "action");
		ac->Settarget(target);
		return ac;
	case enSuperBeam:
		ac = NewGO<Act_superBeam>(0, "action");
		ac->Settarget(target);
		return ac;
	case enObstMove:
		ac = NewGO<Act_ObstMove>(0, "action");
		ac->Settarget(target);
		return ac;
	case enCleanse:
		ac = NewGO<Act_Cleanse>(0, "action");
		ac->Settarget(target);
		return ac;
	}
	return nullptr;
}
