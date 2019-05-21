#pragma once
#include "../MonsterAction.h"

class Act_debuffAtcPow : public MonsterAction
{
public:
	Act_debuffAtcPow();
	~Act_debuffAtcPow();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 20.f;
	int m_timer = 0;
	float m_ExPow = 0;
	float m_pow = 0;
};

