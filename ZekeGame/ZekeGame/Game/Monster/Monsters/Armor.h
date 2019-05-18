#pragma once

#include "../Monster.h"
class Armor :public Monster
{
public:
	Armor();
private:
	AnimationClip m_anim[7];
};