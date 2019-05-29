#pragma once
class DungeonTCamera;
class Fade;
class DungeonTransition : public GameObject
{
private:
	typedef std::vector<std::string> PyFile;
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetTeamMonsters(int monids[3]) {
		for (int i = 0; i < 3; i++) {
			m_monsterIds[i] = monids[i];
		}
	}
	void SetGameData(PyFile& files, PyFile& eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber, int aimode[6]);
private:
	std::vector<std::string> m_files;
	std::vector<std::string> m_enemyFiles;
	MonsterID m_ids[6];
	int m_monai[6];
	int m_aimode[6];
	int m_dunNum = -1;
private:
	void InitUI();
	void InitModel();
	static const int m_numMonster = 3;
	bool m_isfade = false;
	Fade* m_fade;
	FontRender* m_nextfont = nullptr;
	SkinModelRender* m_back = nullptr;
	std::vector<SkinModelRender*> m_monsters;
	CVector3 m_backPos = CVector3::Zero();
	int m_monsterIds[m_numMonster] = { 0 };
	DungeonTCamera* m_camera = nullptr;
	AnimationClip m_animClip[3][1];
	std::vector<AnimationClip> m_anims;
	CVector3 m_standardPos = CVector3::Zero();
};





class DungeonTCamera : public GameObject {
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetTarget(CVector3 tar) {
		m_target = tar;
	}
private:
	CVector3 m_target = CVector3::Zero();
	CVector3 m_toCameraPos = { 150.0f, 200.0f, 500.0f };
	CVector3 m_pos = { 0.0f, 0.0f, 10.0f };
	double xR = 0.f;
	int count = 0;
	double time = 1.f;
	double time2 = 1.f;
	double timee = 0.f;
	double time4 = 1.f;
	bool neko = false;
};