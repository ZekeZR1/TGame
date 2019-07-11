#pragma once
enum MonsterID;
class DungeonGame : public GameObject
{
public:
	void StartTransition();
	void StartNextDungeon();
	void Relese();
private:
	 typedef std::vector<std::string> PyFile;
	std::vector<std::string> m_files;
	std::vector<std::string> m_enemyFiles;
	MonsterID m_ids[6];
	int m_monai[6] = { 0 };
	int m_aimode[6] = { 0 };
	int m_dunNum = -1;
	bool m_isInGame = false;
	CFont m_font;
	int m_round = 0;
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void PostRender() override;
	int GetCurrentRound() {
		return m_round;
	}
	void SetGameData(PyFile& files, PyFile& eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber, int aimode[6]);
	void NextRound() {
		m_round++;
	}
	void StageClear() {
		m_round = 0;
	}
	void SetInGameMode() {
		m_isInGame = true;
	}
	void ClearInGameMode() {
		m_isInGame = false;
	}
};

