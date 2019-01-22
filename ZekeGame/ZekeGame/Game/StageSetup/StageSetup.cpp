#include "stdafx.h"
#include "StageSetup.h"
#include "../GameData.h"
#include "../Monster/Monster.h"
#include "../Monster/Monsters/TestMons.h"
#include "../Monster/Monsters/Uma.h"
#include <array>

StageSetup::StageSetup()
{
	
}

StageSetup::~StageSetup()
{
}

void StageSetup::PVPSetup(std::vector<std::string> files, int monsterAI[6],MonsterID monids[6])
{
	int team = 0;
	int num = 0;
	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = nullptr;
		switch (monids[i])
		{
		case enTest:
			mon = NewGO<TestMons>(0, "monster");
			break;
		case enUmataur:
			mon = NewGO<Uma>(0, "monster");
			break;
		}
		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);
		std::string* path = new std::string("PythonAIs.");
		//std::string* path = new std::string("");
		*path += files[monsterAI[i]];
		mon->SetpyFile(path->c_str());
		g_mons[i] = mon;

	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}


void StageSetup::DungeonSetup(std::vector<std::string> files, int monsterAI[6], MonsterID monids[6], int DunNumber) {
	int team = 0;
	int num = 0;
	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = nullptr;
		switch (monids[i])
		{
		case enTest:
			mon = NewGO<TestMons>(0, "monster");
			break;
		case enUmataur:
			mon = NewGO<Uma>(0, "monster");
			break;
		}
		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);
		std::string* path = new std::string("PythonAIs.");
		//std::string* path = new std::string("");
		*path += files[monsterAI[i]];
		mon->SetpyFile(path->c_str());
		g_mons[i] = mon;
	}
	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}
