#pragma once
#include "Monster.h"
class TestMons :public GameObject, Monster
{
public:
	bool Start() override;
	void Update() override;

private:
};