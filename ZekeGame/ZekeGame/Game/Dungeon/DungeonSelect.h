#pragma once

class DungeonSelect : public GameObject
{
public:
	DungeonSelect();
	~DungeonSelect();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	std::vector<SpriteRender*> m_sps;
	GameCursor* m_cur;
	CVector3 m_pos;
};

