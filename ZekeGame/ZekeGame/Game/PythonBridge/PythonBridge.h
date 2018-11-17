#pragma once
#include "../Monster/Monster.h"
#include "../GameData.h"
#include <thread>

//static Monster* g_mons[64];
//static int g_buddyCount = 0;
//static int g_enemyCount = 0;
//static int g_meNum = 0;
//static int g_meTeam = 0;

class Monster;
class MonsterActionManeger;
extern bool py_exe(int num, int team, const char* file);
struct ExeData
{
	int num = 0;
	int team = 0;
	const char* file;
};
class PythonBridge:public GameObject
{
public:
	PythonBridge();
	void Update() override;
	void pbInit();
	void py_exe(int num,int team,const char* file);
	void AddExe(int num, int team, const char* file);
	void py_exe();


	CVector3 GetMonsVec(int num)
	{
		return g_mons[num]->Getpos();
	}
private:
	std::vector<std::thread*> threads;
	std::vector<bool> comp;

	std::unique_ptr<std::thread> th;
	bool isExe = false;
	std::vector<ExeData> m_exeDatalist;
	bool m_isExeSeting = false;
	float m_timer = 0.0f;
	bool perfect = false;
	MonsterActionManeger* mam = nullptr;
};