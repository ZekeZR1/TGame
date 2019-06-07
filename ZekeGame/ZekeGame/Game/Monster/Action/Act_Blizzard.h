#pragma once
#include "../MonsterAction.h"
class Act_Blizzard : public MonsterAction
{
public:
	Act_Blizzard();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 20.f;
	int m_timer = 0;
	int m_cooltime = 120;
};

