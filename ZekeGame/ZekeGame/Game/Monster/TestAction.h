#pragma once
#include "MonsterAction.h"

class Monster;
class tesAction :public MonsterAction
{
public:
	bool Action() override;
private:
	int m_ID = 0;
	Monster* m_target = nullptr;
};