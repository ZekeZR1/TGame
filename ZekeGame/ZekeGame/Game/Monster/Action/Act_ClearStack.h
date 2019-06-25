#pragma once
#include "../MonsterAction.h"
class Act_ClearStack : public MonsterAction
{
public:
	Act_ClearStack();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 20.f;
	float m_timer = 0;
	int m_cooltime = 5;
};

