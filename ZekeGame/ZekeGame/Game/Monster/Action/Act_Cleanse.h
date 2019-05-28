#pragma once
#include "../MonsterAction.h"
class Act_Cleanse : public MonsterAction
{
public:
	Act_Cleanse();
	bool Action(Monster*) override;
private:
	bool m_first = true;
	float m_cost = 20;
};

