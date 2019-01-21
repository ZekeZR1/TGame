#pragma once
#include "../MonsterAction.h"

class Monster;
class Act_Leave :public MonsterAction
{
public:
	Act_Leave();
	bool Action(Monster* me) override;
};