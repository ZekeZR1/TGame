#pragma once
class DungeonTCamera;

class DungeonTransition : public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetTeamMonsters(int monids[3]) {
		for (int i = 0; i < 3; i++) {
			m_monsterIds[i] = monids[i];
		}
	}
private:
	static const int m_numMonster = 3;
	SkinModelRender* m_back = nullptr;
	std::vector<SkinModelRender*> m_monsters;
	CVector3 m_backPos = CVector3::Zero();
	int m_monsterIds[m_numMonster] = { 0 };
	DungeonTCamera* m_camera = nullptr;
	AnimationClip m_animation[1];
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
};