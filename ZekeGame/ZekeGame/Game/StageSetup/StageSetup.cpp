#include "stdafx.h"
#include "StageSetup.h"
#include "../GameData.h"
#include "../Monster/Monster.h"
#include "../Monster/Monsters/TestMons.h"
#include <array>

StageSetup::StageSetup()
{
	Monster* mons = NewGO<TestMons>(0, "monster");
	mons->Setpos({ 0,0,500 });
	mons->Setnum(0);
	mons->Setteam(0);
	mons->SetpyFile("testBrain");
	//g_mons.push_back(mons);
	g_mons[0] = mons;

	mons = NewGO<TestMons>(0, "monster");
	mons->Setpos({ 250,0,500 });
	mons->Setnum(1);
	mons->Setteam(0);
	mons->SetpyFile("testBrain");
	//g_mons.push_back(mons);
	g_mons[1] = mons;

	mons = NewGO<TestMons>(0, "monster");
	mons->Setpos({ -250,0,500 });
	mons->Setnum(2);
	mons->Setteam(0);
	mons->SetpyFile("testBrain");
	//g_mons.push_back(mons);
	g_mons[2] = mons;


	mons = NewGO<TestMons>(0, "monster");
	mons->Setpos({ 0,0,-500 });
	mons->Setnum(3);
	mons->Setteam(1);
	mons->SetpyFile("PythonAIs.testBrain");
	//g_mons.push_back(mons);
	g_mons[3] = mons;

	mons = NewGO<TestMons>(0, "monster");
	mons->Setpos({ 250,0,-500 });
	mons->Setnum(4);
	mons->Setteam(1);
	mons->SetpyFile("testBrain");
	//g_mons.push_back(mons);
	g_mons[4] = mons;

	mons = NewGO<TestMons>(0, "monster");
	mons->Setpos({ -250,0,-500 });
	mons->Setnum(5);
	mons->Setteam(1);
	mons->SetpyFile("testBrain");
	//g_mons.push_back(mons);
	g_mons[5] = mons;

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}

StageSetup::~StageSetup()
{
}
