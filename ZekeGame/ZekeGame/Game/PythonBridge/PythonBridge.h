#pragma once
#include "../Monster/Monster.h"

static Monster* g_mons[64];
static int buddyCount = 0;
static int enemyCount = 0;

class Monster;
class PythonBridge:public GameObject
{
public:
	void py_exe(Monster* meMons);

	CVector3 GetMonsVec(int num)
	{
		return g_mons[num]->Getpos();
	}
private:
};