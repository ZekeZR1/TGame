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
	bool m_bmenu = false;						//mouseover no 
	bool m_bopen = false;						//mouseover no 
	bool m_bsave = false;						//mouseover no 

	CVector3 m_position2 = CVector3::Zero();
	CVector3 m_position3 = CVector3::Zero();
	CVector3 m_position4 = CVector3::Zero();
	CVector3 m_position5 = CVector3::Zero();

	SpriteRender* m_spriterender2 = nullptr;
	SpriteRender* m_spriterender3 = nullptr;
	SpriteRender* m_spriterender4 = nullptr;
	SpriteRender* m_spriterender5 = nullptr;
	FontRender* m_fmenu = nullptr;				//menu no font
	FontRender* m_fopen = nullptr;				//open no font
	FontRender* m_fsave = nullptr;				//save no font

	GameCursor* m_gamecursor = nullptr;
	AIEditNodeMenu* m_aieditnodemenu = nullptr;
	AIEditNodeMenuSave* m_aieditnodemenusave = nullptr;
	AIEditNodeMenuOpen* m_aieditnodemenuopen = nullptr;
	AIEditNodeProcess* m_proc = nullptr;

};


