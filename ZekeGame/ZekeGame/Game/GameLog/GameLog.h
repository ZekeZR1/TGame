#pragma once

struct Log
{
	float timeLim = 10.f;
	FontRender* font;
	bool isDead = true;
};
class GameLog :public GameObject
{
public:
	GameLog();
	void OnDestroy();
	static GameLog* GetInst()
	{
		if (instans == NULL)
			instans = NewGO<GameLog>(0, "GameLog");
		return instans;
	}
	static void DelGameLog()
	{
		DeleteGO(instans);
		instans = NULL;
	}


	void Update();

	void MMprint(std::wstring str);

private:
	static GameLog* instans;
	Log* m_logs;

	int m_logMax = 18;
	float m_timeMax = 15.f;
};

static GameLog* gameLog()
{
	return GameLog::GetInst();
}