#pragma once
class PMMonster;

class DungeonAISelect : public GameObject
{
public:
	DungeonAISelect();
	~DungeonAISelect();
	bool Start() override;
	void Update() override;
	void LoadFiles();
private:
	CFont font;
	std::vector<std::string> m_files;
	int monai[6] = { 0 };
	int curpos = 0;
	bool sel = false;
	GameCursor* m_cursor;
	PMMonster* m_pmm = nullptr;
	std::vector<PMMonster*> m_pmms;
	SpriteRender* m_GO = nullptr;
};

