#pragma once
#include "../Monster.h"

class Ringo :public Monster
{
public:
	Ringo();
private:
	AnimationClip m_anim[6];
};