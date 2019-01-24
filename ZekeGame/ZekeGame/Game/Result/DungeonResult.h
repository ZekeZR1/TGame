#pragma once

class DungeonResult :public GameObject
{
public:
	void init(int team)
	{
		m_team = team;
	}
private:
	int m_team = 0;
};