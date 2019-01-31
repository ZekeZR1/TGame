#pragma once

enum Mode;
class GameCursor;
class MenuButton;
class GameMenu :public GameObject
{
public:
	~GameMenu();
	void Release();
	bool Start()override;
	void init(int playmode,int dunnum)
	{
		m_playMode = (Mode)playmode;
		m_dunnum = dunnum;
	}
	void Update() override;

	bool isOpen()
	{
		return m_isOpen;
	}
private:
	Mode m_playMode = (Mode)0;
	int m_dunnum = 0;

	bool m_isOpen = false;

	std::vector<MenuButton*> m_buttons;

	GameCursor* m_cursor = nullptr;
	SpriteRender* m_back = nullptr;
	SpriteRender* m_menu = nullptr;
};