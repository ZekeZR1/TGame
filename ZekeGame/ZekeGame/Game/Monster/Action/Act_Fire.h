#pragma once

#include "../MonsterAction.h"
class Monster;

//ANIMATION AXTRA1
class Act_Fire :public MonsterAction
{
public:
	Act_Fire();
	bool Action(Monster* me) override;
private:
	CEffect* m_effect = nullptr;
	bool m_isPlayAnim = false;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_efs = { 5,5,5 };

	float m_timer = 0.f;
	float m_limit = 5.f;
	bool m_first = true;
};