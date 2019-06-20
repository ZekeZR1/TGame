#pragma once
class GameCursor;
class AIEditNodeMenu;
class AIEditNodeMenuSave;
class AIEditNodeMenuOpen;
class AIEditNodeProcess;
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

	bool GetMenuSelect() {
		return menuselect;
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
	AIEditNodeMenuSave* m_aieditnodemenusave;
	AIEditNodeMenuOpen* m_aieditnodemenuopen;
	GameCursor* m_gamecursor;

	FontRender* m_fmenu = nullptr;				//menu no font
	FontRender* m_fopen = nullptr;				//open no font
	FontRender* m_fsave = nullptr;				//save no font

	bool m_bmenu = false;						//mouseover no 
	bool m_bopen = false;						//mouseover no 
	bool m_bsave = false;						//mouseover no 

	AIEditNodeProcess* m_proc = nullptr;
};


