#include "stdafx.h"
#include "StageSetup.h"
#include "../GameData.h"
#include "../Monster/Monster.h"
#include "../Monster/Monsters/TestMons.h"
#include "../Monster/Monsters/Uma.h"
#include "../SaveLoad/PythonFileLoad.h"
#include <string>
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


void StageSetup::DungeonSetup(PyFile files, PyFile eneFiles, int monsterAI[6], MonsterID monids[6], int dunNumber) {
	int team = 0;
	int num = 0;

	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };

	SetEnemyAI(dunNumber,monsterAI, monids);

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team = 256;

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
		if (!team) {
			//team
			std::string* path = new std::string("PythonAIs.");
			*path += files[monsterAI[i]];
			mon->SetpyFile(path->c_str());
		}
		else{
			//enemy
			std::string* path = new std::string("PythonEnemyAIs.");
			*path += eneFiles[monsterAI[i]];
			mon->SetpyFile(path->c_str());
		}
		g_mons[i] = mon;
	}
	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}

void StageSetup::SetEnemyAI(int dun, int* monAI, MonsterID* monId) {
	switch (dun) {
	case 0:
		monAI[3] = 1;
		monId[3] = enTest;
		monAI[4] = 1;
		monId[4] = enTest;
		monAI[5] = 1;
		monId[5] = enTest;
		break;
	case 1:
		monAI[3] = 1;
		monId[3] = enTest;
		monAI[4] = 1;
		monId[4] = enTest;
		monAI[5] = 1;
		monId[5] = enTest;
		break;
	case 2:
		monAI[3] = 1;
		monId[3] = enTest;
		monAI[4] = 1;
		monId[4] = enTest;
		monAI[5] = 1;
		monId[5] = enTest;
		break;
	case 3:
		monAI[3] = 1;
		monId[3] = enTest;
		monAI[4] = 1;
		monId[4] = enTest;
		monAI[5] = 1;
		monId[5] = enTest;
		break;
	case 4:
		monAI[3] = 1;
		monId[3] = enTest;
		monAI[4] = 1;
		monId[4] = enTest;
		monAI[5] = 1;
		monId[5] = enTest;
		break;
	case 5:
		monAI[3] = 1;
		monId[3] = enTest;
		monAI[4] = 1;
		monId[4] = enTest;
		monAI[5] = 1;
		monId[5] = enTest;
		break;
	case 6:
		monAI[3] = 1;
		monId[3] = enTest;
		monAI[4] = 1;
		monId[4] = enTest;
		monAI[5] = 1;
		monId[5] = enTest;
		break;
	case 7:
		monAI[3] = 1;
		monId[3] = enTest;
		monAI[4] = 1;
		monId[4] = enTest;
		monAI[5] = 1;
		monId[5] = enTest;
		break;
	}
}