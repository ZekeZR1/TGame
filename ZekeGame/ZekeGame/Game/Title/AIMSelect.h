#pragma once

class PvPModeSelect;
class SuperMonsterSelect;
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
		m_ainum = ai;
		m_monnum = mon;
	}

	void SetAI(int ai)
	{
		m_ainum = ai;
	}
	void Setmon(int mon)
	{
		m_monnum = mon;
	}
private:
	GameCursor* m_cursor = nullptr;

	SuperMonsterSelect* m_ppms = nullptr;
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

	bool m_isselC = false;
	bool m_isselO = false;

	SpriteRender* m_Black;
};