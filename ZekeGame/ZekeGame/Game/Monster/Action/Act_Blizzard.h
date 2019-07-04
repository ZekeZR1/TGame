#pragma once
#include "../MonsterAction.h"
#include "cmp/CAct_Beam.h"

class Act_Blizzard : public MonsterAction
{
public:
	Act_Blizzard();
	~Act_Blizzard();
	bool Action(Monster* me) override;
private:
	CAct_Beam m_cBeam;
	CVector3 m_efs = CVector3::One() * 3.5;
	bool m_first = true;
	float m_cost = 0.1f;
	float m_timer = 0;
	int m_cooltime = 5;
	float laserRange = 100;
	float m_grantAbsTime = 0.5;
	float m_damage = 0.06f;
	float m_DoTDamageParam = 1.f;
	int m_DoTEndTime = 50;

};

