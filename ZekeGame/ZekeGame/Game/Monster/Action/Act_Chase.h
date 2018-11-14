#pragma once
#include "../MonsterAction.h"

class Monster;
class Act_Chase :public MonsterAction
{
public:
	bool Action(Monster* me) override;
private:
	
};