#pragma once
#include "../MonsterAction.h"
class Act_Poison : public MonsterAction
{
public:
	Act_Poison();
	bool Action(Monster* me) override;
private:
	bool m_first = true;
	float m_cost = 20.f;
	float m_timer = 0;
	int m_cooltime = 5;
	float m_damage = 0.1f;
	float m_SkillRange = 300;
	CVector3 m_efs = CVector3::One() * 3.5;
};
