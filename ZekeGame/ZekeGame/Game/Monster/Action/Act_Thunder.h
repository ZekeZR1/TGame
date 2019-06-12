#pragma once
#include "../MonsterAction.h"
class Act_Thunder : public MonsterAction
{
public:
	Act_Thunder();
	bool Action(Monster* me) override;
	void GrantAbnormalState(Monster* target, Monster* me);
	bool IsHitting(Monster* mon, Monster* me);
	bool m_first = true;
	float m_cost = 20.f;
	float m_timer = 0;
	int m_cooltime = 5;
	CVector3 m_efs = CVector3::One() * 3.5;
	CEffect* m_efk = nullptr;
	CEffect* m_beamefk = nullptr;
	CVector3 crs;
	float laserRange = 100;
	CVector3 m_targetPosition = CVector3::Zero();
	std::map<Monster*, bool> m_isAbnormal;
	std::map<Monster*, float> m_timerForGrantAbs;
	float m_grantAbsTime = 0.5;
	float m_damage = 0.001;
	int m_DoTEndTime = 50;
};

