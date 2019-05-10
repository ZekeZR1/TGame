#pragma once
#include "../Title/SuperMonsterSelect.h"
class PMMonster;
class Fade;
class ReturnButton;
class DungeonAISelect : public SuperMonsterSelect
{
public:
	DungeonAISelect();
	~DungeonAISelect();
	bool Start() override;
	void Update() override;
	std::vector<std::string> GetFiles() override;
	void SetDungeonNumber(int n) {
		m_dunNum = n;
	}
	void LoadFiles();
private:
	CFont font;
	std::vector<std::string> m_files;
	std::vector<std::string> m_enemyFiles;
	int monai[6] = { 0 };
	int aimode[6];
	int curpos = 0;
	bool sel = false;
	GameCursor* m_cursor;
	PMMonster* m_pmm = nullptr;
	std::vector<PMMonster*> m_pmms;
	SpriteRender* m_GO = nullptr;
private:
	static const int m_numMonster = 6;
	const int m_numPmm = 3;
	int m_dunNum = -1;
	SpriteRender* m_dunSp = nullptr;
	SpriteRender* m_backSp = nullptr;
	FontRender* m_font = nullptr;
	Fade* m_fade = nullptr;
	bool m_isfade = false;
	bool isfade = false;
	MonsterID moid[m_numMonster];

	ReturnButton* m_returnButton = nullptr;		//–ß‚éƒ{ƒ^ƒ“
};

