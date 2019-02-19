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
};