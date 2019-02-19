#pragma once
#include "../MonsterAction.h"

class Monster;
class Act_Atack :public MonsterAction
{
public:
	Act_Atack();
	bool Action(Monster* me) override;
private:
	bool m_isfirst = true;
	Sound s;
};