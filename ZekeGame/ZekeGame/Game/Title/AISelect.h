#pragma once

class SuperMonsterSelect;
class PvPModeSelect;
class AIMSelect;
class GameCursor;
class PMMonster;
class IconAI;
class AISelect :public GameObject
{
public:
	~AISelect();
	bool Start();
	void init(PMMonster* pmm,AIMSelect* aims);
	void Update();
	void PostRender();
private:
	PMMonster* m_pmm;
	AIMSelect* m_AIMS;
	GameCursor* m_cursor = nullptr;
	SpriteRender* m_back = nullptr;

	float m_minScroll = 0.0f;
	float m_maxScroll = 0.0f;
	float m_scroll = 316.5f;

	std::vector<IconAI*> m_icons;
	SuperMonsterSelect* m_ppms = nullptr;
	CFont font;

	SpriteRender* m_AIsel = nullptr;
};