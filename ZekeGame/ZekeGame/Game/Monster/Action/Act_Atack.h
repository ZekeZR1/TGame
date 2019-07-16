#pragma once
#include "../MonsterAction.h"

class Monster;
class Act_Atack :public MonsterAction
{
public:
	Act_Atack();
	bool Action(Monster* me) override;
private:
	bool Chase(Monster* me);
	bool Attack(Monster* me);
	enum state
	{
		enSChase,
		enSAttack,
	};
	state m_state = enSChase;
	bool m_isfirst = true;
	Sound* s = nullptr;
};