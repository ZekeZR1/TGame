#pragma once

class GameCursor;
class SuperMonsterSelect;
class MonAIPresetLoad :public GameObject
{
public:
	bool Start();
	void init(SuperMonsterSelect* sms,int num,GameCursor* cursor);
	void Update();
private:
	SpriteRender* m_button = nullptr;
	FontRender* m_font = nullptr;
	GameCursor* m_cursor = nullptr;

	SuperMonsterSelect* m_sms = nullptr;
	int m_num = 0;
};