#include "stdafx.h"
#include "Act_debuffDefPow.h"
#include "../MonsterAction.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_debuffDefPow::Act_debuffDefPow()
{
}


Act_debuffDefPow::~Act_debuffDefPow()
{
}

bool Act_debuffDefPow::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;

		m_first = false;
	}
	return false;
}
