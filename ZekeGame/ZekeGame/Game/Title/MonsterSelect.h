#pragma once
#include "../GameData.h"
class PMMonster;
class AIMSelect;
class GameCursor;
class IconMon;
class MonsterSelect :public GameObject
{
public:
	~MonsterSelect();
	bool Start();
	void init(PMMonster* pmm,AIMSelect* aims);
	void Update();
private:
	GameCursor* m_cursor = nullptr;

	PMMonster* m_pmm;
	AIMSelect* m_aims;
	MonsterID m_selmon = enTest;
	SpriteRender* m_back;
	CVector3 m_backsize = { 148,148,0 };

	std::vector<IconMon*> m_icons;
	CVector2 m_iconsize = { 128,128 };

	std::vector<std::wstring> m_paths;

	int m_monstercount = 3;

	SpriteRender* m_monsel = nullptr;
};