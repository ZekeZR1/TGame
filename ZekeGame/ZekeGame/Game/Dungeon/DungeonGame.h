#pragma once
enum MonsterID;
class DungeonGame : public GameObject
{
public:
	void StartTransition();
private:
	 typedef std::vector<std::string> PyFile;
	std::vector<std::string> m_files;
	std::vector<std::string> m_enemyFiles;
	MonsterID m_ids[6];
	int m_monai[6];
	int m_dunNum = -1;
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetGameData(PyFile& files, PyFile& eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber);
};

