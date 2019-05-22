#pragma once

#include "../Monster.h"

class Book :public Monster
{
public:
	Book();
private:
	AnimationClip m_anim[6];		//anime
};