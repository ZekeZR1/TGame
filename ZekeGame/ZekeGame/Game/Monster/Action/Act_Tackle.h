#pragma once

#include "../MonsterAction.h"

class Monster;

//ANIMATION AXTRA1
class Act_Tackle :public MonsterAction
{
public:
	Act_Tackle();
	bool Action(Monster* me) override;
private:
	bool ismp = true;
	CVector3 rush = CVector3::Zero();
	float m_time = 0.0f;
};