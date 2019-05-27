#pragma once

enum Mode;
class GameCursor;
class MenuButton;

class Game;
class Fade;
class GameMenu :public GameObject
{
public:
	~GameMenu();
	void OnDestroy() override;
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

	void DO()
	{
		m_isdo = true;
	}
	void NOTDO()
	{
		m_isdo = false;
	}
private:
	Mode m_playMode = (Mode)0;
	int m_dunnum = 0;

	bool m_isOpen = false;

	std::vector<MenuButton*> m_buttons;

	GameCursor* m_cursor = nullptr;
	SpriteRender* m_back = nullptr;
	SpriteRender* m_menu = nullptr;

	bool m_isdo = false;					//開けるか？

	Game* m_game = nullptr;					//ゲームのpointa
	Fade* m_fade = nullptr;					//fade
	bool m_isFade = false;					//ファデしてますか？
	int m_bnum = 0;							//どのボタンをクリックしたか
};