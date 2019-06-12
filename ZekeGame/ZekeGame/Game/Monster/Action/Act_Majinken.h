#pragma once
#include "../MonsterAction.h"
class Act_Majinken : public MonsterAction
{
public:
	Act_Majinken();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	bool m_attacked = false;
	float m_cost = 20.f;
	float m_timer = 0;
	float m_damagePow = 100.f;
	int m_chargeTime = 100;
	int m_cooltime = 1000;
	CVector3 knock;
};

