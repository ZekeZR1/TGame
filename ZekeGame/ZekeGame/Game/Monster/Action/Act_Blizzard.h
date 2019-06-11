#pragma once
#include "../MonsterAction.h"
class Act_Blizzard : public MonsterAction
{
public:
	Act_Blizzard();
	bool Action(Monster* me) override;
private:
	void GrantAbnormalState(Monster* target,Monster* me);
	bool IsHitting(Monster* mon, Monster* me);
	bool m_first = true;
	float m_cost = 20.f;
	float m_timer = 0;
	int m_cooltime = 3;
	CVector3 m_efs = { 5,5,5 };
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

