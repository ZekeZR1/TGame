#pragma once
#include "../MonsterAction.h"

class Act_debuffDefPow : public MonsterAction
{
public:
	Act_debuffDefPow();
	~Act_debuffDefPow();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 20.f;
};

