#pragma once

struct Log
{
	float timeLim = 10.f;
	FontRender* font = nullptr;
	bool isDead = true;
};
class GameLog :public GameObject
{
public:
	GameLog();
	void OnDestroy();
	static GameLog* GetInst()
	{
		return instans;
	}
	static void DelGameLog()
	{
		DeleteGO(instans);
		instans = NULL;
	}
	static void NewGameLog()
	{
		instans = NewGO<GameLog>(0, "GameLog");
	}


	void Update();

	void MMprint(std::wstring str);

private:
	static GameLog* instans;
	Log* m_logs = nullptr;

	int m_logMax = 18;
	float m_timeMax = 15.f;
};

static GameLog* gameLog()
{
	return GameLog::GetInst();
}

static void MMprint(std::wstring str)
{
	GameLog* gl = gameLog();
	if (gl != NULL)
		gl->MMprint(str);
}