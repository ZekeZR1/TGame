#pragma once

#include "../MonsterAction.h"

class Act_SpecialAttack :public MonsterAction
{
public:
	Act_SpecialAttack();
	bool Action(Monster* me) override;

	bool Chase(Monster* me);
	bool Attack(Monster* me);
	
private:
	enum state
	{
		enSChase,
		enSAttack,
	};
	state m_state = enSChase;
	CEffect* m_ef = nullptr;
	bool m_isFirst = true;
};