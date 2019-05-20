#include "stdafx.h"
#include "Act_buffAtcPow.h"
#include "../MonsterAction.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_buffAtcPow::Act_buffAtcPow()
{
}


Act_buffAtcPow::~Act_buffAtcPow()
{
}

bool Act_buffAtcPow::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		float atc = me->GetAttack();
		me->SetAttackPower(atc * 1.5);
		m_first = false;
	}
	return false;
}
