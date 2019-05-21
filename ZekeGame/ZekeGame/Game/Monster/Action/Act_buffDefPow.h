#pragma once
#include "../MonsterAction.h"

class Act_buffDefPow : public MonsterAction
{
public:
	Act_buffDefPow();
	~Act_buffDefPow();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 20.f;

};

