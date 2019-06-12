#pragma once
#include "../Monster.h"

class RedHead :public Monster
{
public:
	RedHead();

private:
	AnimationClip m_anim[8];
};