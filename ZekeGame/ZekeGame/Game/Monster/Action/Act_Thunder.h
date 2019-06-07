#pragma once
#include "../MonsterAction.h"
class Act_Thunder : public MonsterAction
{
public:
	Act_Thunder();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 20.f;
	int m_timer = 0;
	int m_cooltime = 120;
	float m_damPow = 30.f;
};

