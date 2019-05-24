#pragma once
#include "../MonsterAction.h"

class Act_buffAtcPow : public MonsterAction
{
public:
	Act_buffAtcPow();
	~Act_buffAtcPow();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 20.f;
	int m_timer = 0;
	int m_clearTime = 120;
	float m_pow = 0;
	float m_ExPow = 0;
	int m_cooltime = 120;
};

