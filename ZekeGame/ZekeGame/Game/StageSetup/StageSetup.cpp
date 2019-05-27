#include "stdafx.h"
#include "StageSetup.h"
#include "../GameData.h"
#include "../Monster/Monster.h"
#include "../Monster/Monsters/TestMons.h"
#include "../Monster/Monsters/Uma.h"
#include "../Monster/Monsters/Fairy.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "..//Dungeon/DungeonData.h"
#include <string>
#include <array>

StageSetup::StageSetup()
{
	
}

StageSetup::~StageSetup()
{
}

void StageSetup::SuddenDeath(const char* files[6], MonsterID monids[6], int teams[6])
{
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		DeleteGO(mon);
	}

	CVector3 poss[6];
	poss[0] = { 250,0,500 };
	poss[1] = { 0,0,500 };
	poss[2] = { -250,0,500 };
	poss[3] = { 250,0,-500 };
	poss[4] = { 0,0,-500 };
	poss[5] = { -250,0,-500 };
	int poi = 0;

	bool isp = true;
	for (int i = 0; i < 6; i++)
	{
		if (monids[i] == -1)
			break;
		if (teams[i] == 1 && isp)
		{
			poi = 3;
			isp = false;
		}
		Monster* mon = GameData::LoadMonster(monids[i]);
		mon->Setpos(poss[poi]);
		mon->Setnum(i);
		mon->Setteam(teams[i]);
		//mon->SetpyFile(files[i]);
		g_mons[i] = mon;

		mon->SuddenDeath();
		g_mons[i] = mon;

		poi++;
	}
}

void StageSetup::PVPSetup(std::vector<std::string> files, int monsterAI[6],MonsterID monids[6], int AImode[6])
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
		std::string* path;

		mon = GameData::LoadMonster(monids[i]);
		

		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);
		
		//pythonとVisualScriptの仕分け
		if (AImode[i] == 0)
		{
			path = new std::string("PythonAIs.");
			*path += files[monsterAI[i]];
			mon->SetpyFile(path);
		}
		else
		{
			path = new std::string("Assets/VisualAI/");
			char wc[64];
			sprintf_s(wc, "%03d.va", monsterAI[i]);
			*path += wc;
			mon->SetVisualScriptAI(path);
		}

		g_mons[i] = mon;

	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}


void StageSetup::DungeonSetup(PyFile files, PyFile eneFiles, int monsterAI[6], MonsterID monids[6], int dunNumber, int AImode[6]) {
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
			team++;

		Monster* mon = GameData::LoadMonster(monids[i]);
		auto vaFiles = VisualAiFileLoad::FilesLoad();

		/*switch (monids[i])
		{
		case enTest:
			mon = NewGO<TestMons>(0, "monster");
			break;
		case enUmataur:
			mon = NewGO<Uma>(0, "monster");
			break;
		}*/
		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);
		if (team == 0) {
			//team
			//pythonとVisualScriptの仕分け
			if (AImode[i] == 0)
			{
				std::string* path = new std::string("PythonAIs.");
				*path += files[monsterAI[i]];
				mon->SetpyFile(path);
			}
			else
			{
				std::string* path = new std::string("Assets/VisualAI/");
				*path += vaFiles[monsterAI[i]];
				*path += ".va";
				mon->SetVisualScriptAI(path);
			}
		}
		else{
			//enemy
			std::string* path = new std::string("PythonEnemyAIs.");
			*path += eneFiles[monsterAI[i]];
			mon->SetpyFile(path);
		}
		g_mons[i] = mon;
	}
	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}

//dungeon enemy ai and id
void StageSetup::SetEnemyAI(int dun, int* monAI, MonsterID* monId) {
	//TODO : Zeke : ダンジョンの敵AIの調整
	int round = IDungeonData().GetRound();
	switch (dun) {
	case 0:
		monAI[3] = 0;
		monId[3] = enFairy;
		monAI[4] = 0;
		monId[4] = enTest;
		monAI[5] = 0;
		monId[5] = enFairy;
		break;
	case 1:
		if (round == 0) {
			monAI[3] = 0;
			monId[3] = enFairy;
			monAI[4] = 0;
			monId[4] = enFairy;
			monAI[5] = 0;
			monId[5] = enFairy;
		}
		if (round == 1) {
			monAI[3] = 1;
			monId[3] = enArmor;
			monAI[4] = 1;
			monId[4] = enBook;
			monAI[5] = 1;
			monId[5] = enArmor;
		}
		break;
	case 2:
		monAI[3] = 1;
		monId[3] = enUmataur;
		monAI[4] = 1;
		monId[4] = enUmataur;
		monAI[5] = 1;
		monId[5] = enUmataur;
		break;
	case 3:
		monAI[3] = 1;
		monId[3] = enUmataur;
		monAI[4] = 1;
		monId[4] = enUmataur;
		monAI[5] = 1;
		monId[5] = enUmataur;
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

void StageSetup::OshiFes()
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

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180);

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = nullptr;
		std::string* path = nullptr;
		if (i == 3)
		{
			mon = GameData::LoadMonster(enFairy);

			path = new std::string("PythonAIs.1Q");
			//path = new std::string("1Q");
		}
		else if (i == 4 || i == 5)
		{
			mon = GameData::LoadMonster(enUmataur);

			path = new std::string("PythonAIs.1Q");
			//path = new std::string("1Q");
		}
		else
		{
			mon = GameData::LoadMonster(enUmataur);

			path = new std::string("PythonAIs.1A");
			//path = new std::string("1A");
		}
		if (i < 3)
			mon->SetRotation(rot);

		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);

		
		mon->SetpyFile(path);
		g_mons[i] = mon;

	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}

void StageSetup::OshiFes2()
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

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), 180);

	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
			team++;

		Monster* mon = nullptr;
		std::string* path;
		if (i == 3)
		{
			mon = GameData::LoadMonster(enFairy);

			path = new std::string("PythonAIs.");
			//std::string* path = new std::string("");
			*path += "2Q";
		}
		else if (i == 4 || i == 5)
		{
			mon = GameData::LoadMonster(enUmataur);

			path = new std::string("PythonAIs.");
			//std::string* path = new std::string("");
			*path += "2Q";
		}
		else if(i == 2)
		{
			mon = GameData::LoadMonster(enFairy);

			path = new std::string("PythonAIs.");
			//std::string* path = new std::string("");
			*path += "2A-fairy";
			//*path += files[monsterAI[i]];
		}
		else
		{
			mon = GameData::LoadMonster(enUmataur);

			path = new std::string("PythonAIs.");
			//std::string* path = new std::string("");
			*path += "2A-uma";
			//*path += files[monsterAI[i]];
		}
		if (i < 3)
			mon->SetRotation(rot);

		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);

		mon->SetpyFile(path);
		g_mons[i] = mon;

	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
}

void StageSetup::StageSet(int stage) {
	switch (stage) {
	case 0:
	{
		/*SkinModelRender* stageModel = NewGO<SkinModelRender>(0, "stageModel");
		stageModel->Init(L"Assets/modelData/Test.cmo");
		stageModel->SetPosition(CVector3::Zero());*/
	}
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

void StageSetup::NetworkPvPSetup(std::vector<std::string> files,
	std::vector<std::string> enemyFiles,
	int monsterAI[6],
	int monids[6],
	int aimode[6]
	) {
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
		std::string* path;
		auto vaFiles = VisualAiFileLoad::FilesLoad();
		mon = GameData::LoadMonster(monids[i]);
		if (team == 0) {
			//My team data
			if (aimode[i] == 0) {
				path = new std::string("PythonAIs.");
				*path += files[i];
			}
			else {
				path = new std::string("Assets/VisualAI/");
				*path += vaFiles[monsterAI[i]];
				*path += ".va";
				//sprintf_s(wc, "%03d.va", monsterAI[i]);
				mon->SetVisualScriptAI(path);
				//*path += files[monsterAI[i]];
				//mon->SetVisualScriptAI(path);
			}
		}
		else {
			//Enemy team data
			if (aimode[i] == 0) {
				path = new std::string("NetworkEnemyAIs.");
				*path += enemyFiles[i - 3];
			}
			else {
				path = new std::string("NetworkEnemyAIs/");
				//*path += files[monsterAI[i]];
				auto n = std::to_string(i - 2);
				*path += n;
				*path += "enemy.va";
				mon->SetVisualScriptAI(path);
			}
		}
		mon->Setpos(poss[i]);
		mon->Setnum(i);
		mon->Setteam(team);

		mon->SetpyFile(path);
		g_mons[i] = mon;
		//delete path;
	}

	g_buddyCount = 3;
	g_enemyCount = 3;
	g_monsCount = 6;
	//int team = 0;
	//int num = 0;
	//CVector3 poss[6];
	//poss[0] = { 250,0,500 };
	//poss[1] = { 0,0,500 };
	//poss[2] = { -250,0,500 };
	//poss[3] = { 250,0,-500 };
	//poss[4] = { 0,0,-500 };
	//poss[5] = { -250,0,-500 };
	////load my team
	//for (int i = 0; i < 3; i++) {
	//	Monster* mon = nullptr;
	//	std::string* path;

	//	mon = GameData::LoadMonster(myMonsterId[i]);
	//	path = new std::string("PythonAIs.");
	//	//*path += files[monsterAI[i]];
	//	*path += files[myMonAI[i]];

	//	mon->Setpos(poss[i]);
	//	mon->Setnum(i);
	//	mon->Setteam(team);

	//	mon->SetpyFile(path);
	//	g_mons[i] = mon;
	//	delete path;
	//}
	////load enemy team
	//team++;
	//for (int i = 3; i < 6; i++) {
	//	Monster* mon = nullptr;
	//	std::string* path;

	//	mon = GameData::LoadMonster(enemyMonsterId[i - 3]);
	//	path = new std::string("PythonAIs.");
	//	//*path += files[];
	//	*path += files[myMonAI[i - 3]];

	//	mon->Setpos(poss[i]);
	//	mon->Setnum(i);
	//	mon->Setteam(team);

	//	mon->SetpyFile(path);
	//	g_mons[i] = mon;
	//	delete path;
	//}
	//g_buddyCount = 3;
	//g_enemyCount = 3;
	//g_monsCount = 6;
}
