#pragma once

class GameCursor;
class MenuButton;
class GameMenu :public GameObject
{
public:
	~GameMenu();
	bool Start()override;
	void Update() override;

	bool isOpen()
	{
		return m_isOpen;
	}
private:
	bool m_isOpen = false;

	std::vector<MenuButton*> m_buttons;

	GameCursor* m_cursor = nullptr;
	SpriteRender* m_back = nullptr;
	SpriteRender* m_menu = nullptr;
};