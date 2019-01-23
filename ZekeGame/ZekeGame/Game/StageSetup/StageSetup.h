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
	static void PVPSetup(std::vector<std::string> files,int monsterAI[6],MonsterID monids[6]);
	static void DungeonSetup(PyFile files,PyFile eneFile, int monsterAI[6], MonsterID monids[6],int DunNumber);
private:
	static void SetEnemyAI(int, int* monAI, MonsterID* monId);
};
