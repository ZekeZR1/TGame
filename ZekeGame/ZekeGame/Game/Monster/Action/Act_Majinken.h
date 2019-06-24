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
	float m_cost = 15.f;
	float m_timer = 0;
	float m_damagePow = 70.f;
	int m_chargeTime = 100;
	int m_cooltime = 300;
	CVector3 knock;
	CEffect* m_efk = nullptr;
};

