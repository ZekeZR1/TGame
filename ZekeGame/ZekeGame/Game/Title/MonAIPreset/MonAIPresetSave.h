#pragma once

class GameCursor;
class SuperMonsterSelect;

struct chank
{
	int monID = 0;
	int stlen = 0;
	char* str = nullptr;

};
class MonAIPresetSave :public GameObject
{
public:
	bool Start();
	void init(SuperMonsterSelect* ppms,int No);
	void Update();
private:
	SpriteRender* m_button = nullptr;
	FontRender* m_font = nullptr;
	GameCursor* m_cursor = nullptr;

	int num = 0;
	SuperMonsterSelect* m_ppms = nullptr;
};