#pragma once
#include "SuperMonsterSelect.h"
class PMMonster;
class GameCursor;
class SuperMonsterSelect;
class PvPModeSelect :public SuperMonsterSelect
{
public:
	~PvPModeSelect();
	bool Start() override;
	void Update() override;
	void PostRender() override;
	void LoadFiles();
	
	std::vector<std::string> GetFiles()
	{
		return m_files;
	}
private:
	CFont font;
	std::vector<std::string> m_files;
	int monai[6] = {0};
	int curpos = 0;
	bool sel = false;

	GameCursor* m_cursor;

	PMMonster* m_pmm = nullptr;
	std::vector<PMMonster*> m_pmms;
	//std::vector<SpriteRender*> m_monicon;

	SpriteRender* m_GO = nullptr;
	SpriteRender* m_back = nullptr;

	SpriteRender* m_return = nullptr;
	SpriteRender* m_returnMoji = nullptr;
	bool isReturnOver = false;
	CVector2 m_returnS = { 604,256 };

	Sound* m_BGM = nullptr;
};