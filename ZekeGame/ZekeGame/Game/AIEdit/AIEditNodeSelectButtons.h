#pragma once
class GameCursor;
class AIEditNodeMenu;
class AIEditNodeSelectButtons : public GameObject
{

public:

	~AIEditNodeSelectButtons();

	bool Start();
	void Update();

	void Setmenuselect(bool a)
	{

		menuselect = a;
	}

private:

	bool menuselect = false;

	CVector3 m_position2 = CVector3::Zero();
	CVector3 m_position3 = CVector3::Zero();
	CVector3 m_position4 = CVector3::Zero();
	CVector3 m_position5 = CVector3::Zero();

	SpriteRender* m_spriterender2;
	SpriteRender* m_spriterender3;
	SpriteRender* m_spriterender4;
	SpriteRender* m_spriterender5;

	AIEditNodeMenu* m_aieditnodemenu;
	GameCursor* m_gamecursor;

};


