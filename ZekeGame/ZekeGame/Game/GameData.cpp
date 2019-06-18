#include "stdafx.h"
#include "GameData.h"
#include "Monster/Monsters/TestMons.h"
#include "Monster/Monsters/Uma.h"
#include "Monster/Monsters/Fairy.h"
#include "Monster/Monsters/Armor.h"
#include "Monster/Monsters/Goblin.h"
#include "Monster/Monsters/Book.h"
#include "Monster/Monsters/RedHead.h"
#include "Monster/Monsters/kikyo.h"
#include "Monster/Monsters/ShikoChu.h"
#include "Monster/Monsters/Ringo.h"


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
	case enArmor:
		mon = NewGO<Armor>(0, "monster");
		break;
	case enGoblin:
		mon = NewGO<Goblin>(0, "monster");
		break;
	case enBook:
		mon = NewGO<Book>(0, "monster");
		break;
	case enRedHead:
		mon = NewGO<RedHead>(0, "monster");
		break;
	case enKikyo:
		mon = NewGO<Kikyo>(0, "monster");
		break;
	case enShikoChu:
		mon = NewGO<ShikoChu>(0, "monster");
		break;
	case enRingo:
		mon = NewGO<Ringo>(0, "monster");
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
	case enArmor:
		return L"Assets/sprite/mon_armor.dds";
		break;
	case enGoblin:
		return L"Assets/sprite/mon_gob.dds";
		break;
	case enBook:
		return L"Assets/sprite/mon_book.dds";
		break;
	case enRedHead:
		return L"Assets/sprite/mon_RedHead.dds";
		break;
	case enKikyo:
		return L"Assets/sprite/mon_kikyo.dds";
		break;
	case enShikoChu:
		return L"Assets/sprite/mon_bug.dds";
		break;
	case enRingo:
		return L"Assets/sprite/mon_ringo.dds";
		break;
	}
	return nullptr;
}

const wchar_t* GameData::GetMonsterName(MonsterID id) {
	switch (id)
	{
	case enTest:
		return L"テスト";
		break;
	case enUmataur:
		return L"馬タウロス";
		break;
	case enFairy:
		return L"妖精";
		break;
	case enArmor:
		return L"鎧";
		break;
	case enGoblin:
		return L"ゴブリン";
		break;
	case enBook:
		return L"本";
		break;
	case enRedHead:
		return L"レッドヘッド";
		break;
	case enKikyo:
		return L"キキョウ";
		break;
	case enShikoChu:
		return L"死光虫";
		break;
	case enRingo:
		return L"りんごちゃん";
		break;
	default:
		assert(false);
		break;
	}
}

ActionID* GameData::GetMonsterActions(int monsterID, int& count)
{
	ActionID* ua = nullptr;
	count = 0;
	switch (monsterID)
	{
	case enTest:
		count = 99;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enActNone;
		ua[6] = enSuperBeam;
		ua[7] = enObstMove;
		ua[8] = enCleanse;
		ua[9] = enBuffAtc;
		ua[10] = enDebuffAtc;
		ua[11] = enBuffDef;
		ua[12] = enDebuffDef;
		ua[13] = enMajinken;
		ua[14] = enClearStack;
		ua[15] = enManaHeal;
		ua[16] = enBlizzard;
		ua[17] = enIgnite;
		ua[18] = enPoison;
		ua[19] = enThunder;
		break;
	case enUmataur:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enActNone;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enMajinken;
		break;
	case enFairy:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enRecovery;
		ua[5] = enFire;
		break;
	case enArmor:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enGuardian;
		break;
	case enGoblin:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enPoison;
		ua[5] = enDebuffAtc;
		break;
	case enBook:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enCleanse;
		ua[5] = enClearStack;
		break;
	case enRedHead:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enIgnite;
		ua[5] = enThunder;
		break;
	case enKikyo:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enLeave;
		ua[enDefense] = enDefense;
		ua[4] = enSuperBeam;
		ua[5] = enManaHeal;
		break;
	case enShikoChu:
		count = 2;
		ua = new ActionID[count];
		ua[enAtack] = enSpecialAttack;
		ua[enChase] = enChase;
		break;
	case enRingo:
		count = 6;
		ua = new ActionID[count];
		ua[enAtack] = enAtack;
		ua[enChase] = enChase;
		ua[enLeave] = enActNone;
		ua[enDefense] = enDefense;
		ua[4] = enTackle;
		ua[5] = enMajinken;
		break;
	}
	return ua;
}

ActionID GameData::GetMonsterAction(int monsterID, int actionIndex)
{
	int cnt = 0;
	ActionID* ua = GetMonsterActions(monsterID, cnt);
	
	if (actionIndex >= cnt)
		return ActionID::enActNone;

	ActionID ad = ua[actionIndex];
	delete ua;
	return ad;
}
