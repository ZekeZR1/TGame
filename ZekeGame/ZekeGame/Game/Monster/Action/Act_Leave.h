#pragma once
#include "../MonsterAction.h"

class Monster;
class Act_Leave :public MonsterAction
{
public:
	bool Action(Monster* me) override;
};