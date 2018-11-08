#pragma once
#include "../Monster/Monster.h"

static Monster* g_mons[64];
static int g_buddyCount = 0;
static int g_enemyCount = 0;
static int g_meNum = 0;
static int g_meTeam = 0;

class Monster;
class PythonBridge:public GameObject
{
public:
	void pbInit();
	void py_exe(int num,int team,const char* file);

	CVector3 GetMonsVec(int num)
	{
		return g_mons[num]->Getpos();
	}
private:
};