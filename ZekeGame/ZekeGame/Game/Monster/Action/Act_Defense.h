#pragma once


#include "../MonsterAction.h"

class Monster;
class Act_Defense :public MonsterAction
{
public:
	Act_Defense();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_time = 0;

	float m_def = 0;
	float m_Exdef = 0;
};