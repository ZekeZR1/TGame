#pragma once
#include "../../Engine/graphics/animation/AnimationClip.h"
#include "../Monster.h"
class TestMons :public Monster
{
public:
	TestMons();
	//bool Start() override;
	//void Update() override;
private:
	
	AnimationClip m_animclip[3];
};