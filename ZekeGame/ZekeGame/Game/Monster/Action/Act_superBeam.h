#pragma once
#include "../MonsterAction.h"
#include "cmp/CAct_Beam.h"
class Act_superBeam : public MonsterAction
{
public:
	Act_superBeam();
	bool Action(Monster* me) override;
private:
	CAct_Beam m_cBeam;
	bool m_first = true;
	float m_cost = 20.f;
	float m_timer = 0;
	int m_cooltime = 5;
	float laserRange = 100;
	float m_grantAbsTime = 0.5;
	float m_damage = 0.001;
	int m_DoTEndTime = 50;
};

