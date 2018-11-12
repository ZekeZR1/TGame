#pragma once
#include "Monster.h"
class TestMons :public Monster
{
public:
	TestMons();
	bool Start() override;
	//void Update() override;
private:
};