#pragma once
class GameCursor;
class DungeonResult :public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void init(int team, int num)
	{
		m_team = team;
		m_dunNum = num;
	}
private:
	int m_team = 0;
	int m_dunNum = -1;
	SpriteRender* m_resultSp = nullptr;
	SpriteRender* m_buttonSp = nullptr;
	CVector3 m_buttonPos = {460.f,-200.f,0.f};
	FontRender* m_buttonText = nullptr;
	GameCursor* m_cursor = nullptr;
};