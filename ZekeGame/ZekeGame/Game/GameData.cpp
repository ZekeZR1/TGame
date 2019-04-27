#include "stdafx.h"
#include "GameData.h"
#include "Monster/Monsters/TestMons.h"
#include "Monster/Monsters/Uma.h"
#include "Monster/Monsters/Fairy.h"

Monster* g_mons[64];
int g_buddyCount = 0;
int g_enemyCount = 0;
int g_monsCount = 0;
int g_meNum = 0;
int g_meTeam = 0;

int g_monset[6] = { 1,1,1,1,1,1 };
AIsetData g_AIset[6] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
void GameData::deletemons(Monster * mon)
{
	for (Monster* gmon : g_mons)
	{
		if (gmon == nullptr)
			break;
		for (auto ac : gmon->Getactions())
		{
			if (ac->Gettarget() == mon)
				ac->Settarget(nullptr);
		}
	}
	g_monsCount--;
	for (int i = mon->Getnum(); i < g_monsCount+1; i++)
	{
		g_mons[i] = g_mons[i + 1];
		if(g_mons[i] != NULL)
			g_mons[i]->Setnum(i);
	}
	/*std::vector<Monster*>::iterator ite = std::find(g_mons.begin(), g_mons.end(), mon);
	g_mons.erase(ite);*/
}

Monster * GameData::LoadMonster(int monID)
{
	Monster* mon = nullptr;
	switch (monID)
	{
	case enTest:
		mon = NewGO<TestMons>(0, "monster");
		break;
	case enUmataur:
		mon = NewGO<Uma>(0, "monster");
		break;
	case enFairy:
		mon = NewGO<Fairy>(0, "monster");
		break;
	}
	return mon;
}

const wchar_t * GameData::GetMonsterIconPath(int monID)
{
	switch (monID)
	{
	case enTest:
		return L"Assets/sprite/mon_one.dds";
		break;
	case enUmataur:
		return L"Assets/sprite/mon_uma.dds";
		break;
	case enFairy:
		return L"Assets/sprite/mon_fairy.dds";
		break;
	}
	return nullptr;
}
