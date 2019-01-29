#pragma once

class DungeonResult :public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void init(int team)
	{
		m_team = team;
	}
private:
	int m_team = 0;
	SpriteRender* m_resultSp = nullptr;
};