#pragma once

enum MonsterID;

class DungeonData
{
public:
	typedef std::vector<std::string> PyFile;
	void SetGameData(PyFile files, PyFile eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber);
	PyFile GetFiles() {
		return m_files;
	}
	PyFile GetEnemyFiles() {
		return m_enemyFiles;
	}
	MonsterID* GetMonsterIDs() {
		return m_ids;
	}
	int* GetMonsterAI() {
		return m_monai;
	}
	int GetDungeonNum() {
		return m_dunNum;
	}
	void SetDunNum(int n) {
		m_dunNum = n;
	}
	void SetMonsterID(MonsterID id,int index) {
		m_ids[index] = id;
	}
	void SetRound(int round) {
		m_round = round;
	}
	const int GetRound(){
		return m_round;
	}
	const int GetNumRound(int);
	bool isFinalRound(int DunNum);

	static DungeonData& GetInstance() {
		static DungeonData instance;
		return instance;
	}
private:
	PyFile m_files;
	PyFile m_enemyFiles;
	MonsterID m_ids[6];
	int m_monai[6];
	int m_dunNum = -1;
	int m_currentR = -1;
	int m_round = 0;
	int m_rounds[8] = { 0,1,2,3,2,1,0,0};
};

static DungeonData& IDungeonData() {
	return DungeonData::GetInstance();
}