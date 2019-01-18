#pragma once

class PvPModeSelect;
class PMMonster;
class AISelect;
class MonsterSelect;
class GameCursor;
class AIMSelect :public GameObject
{
public:
	~AIMSelect();
	bool Start() override;
	void Update() override;

	void init(PMMonster* pmm,int ai,int mon)
	{
		m_pmm = pmm;
		m_oan = ai;
		m_omn = mon;
	}

	void SetAI(int ai)
	{
		m_ainum = ai;
	}
	void Setmon(int mon, const wchar_t* path)
	{
		m_monnum = mon;
		m_path = path;
	}
private:
	GameCursor* m_cursor = nullptr;

	PvPModeSelect* m_ppms = nullptr;
	PMMonster* m_pmm = nullptr;

	AISelect* m_AIS = nullptr;
	MonsterSelect* m_MS = nullptr;

	int m_oan = 0;
	int m_omn = 0;
	int m_ainum = 0;
	int m_monnum = 0;
	const wchar_t* m_path;

	SpriteRender* m_can = nullptr;
	SpriteRender* m_cdum = nullptr;

	SpriteRender* m_ok = nullptr;
	SpriteRender* m_odum = nullptr;

	bool m_issel = false;
};