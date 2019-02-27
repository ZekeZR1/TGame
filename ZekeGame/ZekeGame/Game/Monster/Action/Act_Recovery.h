#pragma once


#include "../MonsterAction.h"

class Monster;

class Act_Recovery :public MonsterAction
{
public:
	Act_Recovery();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	CEffect* eff = nullptr;
};