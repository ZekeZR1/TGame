#pragma once


enum MonsterID;

struct InitMonsData
{
	int AI;
	MonsterID monID;
};

class StageSetup
{
private:
	typedef std::vector<std::string> PyFile;
public:
	StageSetup();
	~StageSetup();
	static void SuddenDeath(const char* files[6], MonsterID monids[6], int teams[6]);
	static void PVPSetup(std::vector<std::string> files,int monsterAI[6],MonsterID monids[6]);
	static void DungeonSetup(PyFile files,PyFile eneFile, int monsterAI[6], MonsterID monids[6],int DunNumber);
	static void NetworkPvPSetup(PyFile file,int myMonsterId[3],int myMonAI[3], int enemyMonsterId[3]);
	static void OshiFes();
	static void OshiFes2();
	static void StageSet(int stageNumber);
private:
	static void SetEnemyAI(int, int* monAI, MonsterID* monId);
};
