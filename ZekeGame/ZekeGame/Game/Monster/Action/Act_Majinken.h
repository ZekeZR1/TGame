#pragma once
#include "../MonsterAction.h"
class Act_Majinken : public MonsterAction
{
public:
	Act_Majinken();
	~Act_Majinken();
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

	bool m_first = true;
	bool m_attacked = false;
	float m_cost = 15.f;
	float m_timer = 0;
	float m_damagePow = 70.f;
	int m_chargeTime = 100;
	int m_cooltime = 300;
	CVector3 knock = CVector3::Zero();
	CEffect* m_efk = nullptr;
};

