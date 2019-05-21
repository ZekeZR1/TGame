#include "stdafx.h"
#include "Act_buffDefPow.h"
#include "../MonsterAction.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_buffDefPow::Act_buffDefPow()
{
}


Act_buffDefPow::~Act_buffDefPow()
{
}


bool Act_buffDefPow::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;

		m_first = false;
	}
	return false;
}