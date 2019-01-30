#pragma once
class StageSelect : public GameObject
{
private:
	typedef std::vector<std::string> PyFile;
public:
	StageSelect();
	~StageSelect();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetDungeonGameData(PyFile& files, PyFile& eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber) {
		m_files = files;
		m_enemyFiles = eneFile;
		for (int i = 0; i < 6; i++) {
			m_monai[i] = monsterAI[i];
			m_ids[i] = monids[i];
		}
		m_dunNum = DunNumber;
		m_mode = enDungeon;
	}
private:
	std::vector<std::string> m_files;
	std::vector<std::string> m_enemyFiles;
	MonsterID m_ids[6];
	int m_monai[6];
	int m_dunNum = -1;
private:
	enum SelectMode {
		enDungeon,
		enLocalPvP,
		enOnlinePvP
	};
	SelectMode m_mode;
	CVector3 m_firstImgaePos = { -300.f,200.f,0.f };
	std::vector<SpriteRender*> m_stageImages;
	const int m_NumStage = 3;
	const float m_stageImageW = 300.f;
	const float m_stageImageH = 200.f;
	CVector3 m_stageImageStandardPos = CVector3::Zero();
	const CVector2 m_distanceToOtherStageImage = { 500.f,-400.f };
	std::map<SpriteRender*, int> m_stageNumberMap;
	GameCursor* m_cur = nullptr;
};

