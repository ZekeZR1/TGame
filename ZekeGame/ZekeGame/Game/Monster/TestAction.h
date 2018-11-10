#pragma once
#include "MonsterAction.h"

class Monster;
class tesAction :public MonsterAction
{
public:
	bool Action(Monster* me) override;
private:
	
};