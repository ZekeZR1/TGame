#pragma once
#include "../MonsterAction.h"

class Monster;
class Act_Atack :public MonsterAction
{
public:
	bool Action(Monster* me) override;
private:
};