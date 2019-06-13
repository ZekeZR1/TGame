#pragma once

#include "../MonsterAction.h"

class Act_SpecialAttack :public MonsterAction
{
public:
	Act_SpecialAttack();
	bool Action(Monster* me) override;
private:
	CEffect* m_ef = nullptr;
	bool m_isFirst = true;
};