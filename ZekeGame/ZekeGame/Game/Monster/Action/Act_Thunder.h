#pragma once
#include "../MonsterAction.h"
#include "cmp/CAct_Beam.h"

class Act_Thunder : public MonsterAction
{
public:
	Act_Thunder();
	bool Action(Monster* me) override;
private:
	CAct_Beam m_cBeam;
	CVector3 m_efs = CVector3::One() * 3.5;
	bool m_first = true;
	float m_cost = 20.f;
	float m_timer = 0;
	int m_cooltime = 5;
	float laserRange = 100;
	float m_grantAbsTime = 0.5;
	float m_damage = 0.001;
	int m_DoTEndTime = 50;
};

