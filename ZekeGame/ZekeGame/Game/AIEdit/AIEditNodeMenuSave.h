#pragma once

class AIEditNodeProcess;
class AIEditNodeMenu;
class AIEditNodeSelectButtons;
class AIEditNodeMenuSave :public GameObject
{

public:

	~AIEditNodeMenuSave();

	bool Start();
	void Update();
	void Confirmation();

private:

	int button = 2;
	bool click = false;   //選択したらtrueになる。
	bool clickyes = false;  //はいを選択したらtrueになる。
	bool stop = false;

	std::vector<SpriteRender*> sp;
	std::vector<SpriteRender*> m_buttons;
	SpriteRender* m_spriteRender;
	SpriteRender* m_spriteRender2;
	SpriteRender* m_spriteRender3;
	std::vector<FontRender*> m_fonts;
	FontRender* m_fonts2;
	FontRender* m_fonts3;
	FontRender* m_fonts4;

	GameCursor* m_gamecursor;
	
	AIEditNodeMenu* m_aieditnodemenu;
	AIEditNodeProcess* m_aieditnodeprocess;
	AIEditNodeSelectButtons* m_aieditselectbuttons;

	CVector3 cursorpos = CVector3::Zero();

	CVector3 confpos = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();
	CVector3 m_positionselect2 = CVector3::Zero();
	CVector3 m_Confirmationposition = CVector3::Zero();
	CVector2 m_fontpos = CVector2::Zero();
	CVector2 m_fontpos2 = CVector2::Zero();
	CVector2 m_fontpos3 = CVector2::Zero();

};