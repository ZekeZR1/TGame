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
private:
	PyFile m_files;
	PyFile m_enemyFiles;
	MonsterID m_ids[6];
	int m_monai[6];
	int m_dunNum = -1;
	int m_round = -1;
};

static DungeonData& IDungeonData() {
	static DungeonData dungeonData;
	return dungeonData;
}