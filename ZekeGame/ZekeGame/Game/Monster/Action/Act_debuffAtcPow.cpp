#include "stdafx.h"
#include "Act_debuffAtcPow.h"
#include "../MonsterAction.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_debuffAtcPow::Act_debuffAtcPow()
{
}


Act_debuffAtcPow::~Act_debuffAtcPow()
{
}

bool Act_debuffAtcPow::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;

		m_first = false;
	}
	return false;
}