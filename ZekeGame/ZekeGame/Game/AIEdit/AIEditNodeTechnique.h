#pragma once
class GameCursor;
class GameCamera;

class AIEditNodeButton;
class AIEditNodeOrder;
class AIEditNodeProcess;
class AIEditNodeSelectFonts;
class AIEditNodeTechnique : public GameObject
{

public:

	~AIEditNodeTechnique();


	bool Start();
	void Update();
	void Order();

	bool GetTec()
	{

		return Tec;
	}

	enum Technique {

		enAttak = 500,
		enEscape,
		enCase,
		enProtect,
		enHeel,
		enSpecial1,
		enSpecial2,
		ennull = 0,
	};

	int Gettechnique()
	{

		return m_technique;
	}

	bool Gettechniquefont()
	{
		return techniquefont;
	}

private:

	Technique m_technique = ennull;
	bool Tec = false;
	bool Choice4 = false;
	int button = 7;
	int techniquefont = false;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	SpriteRender * m_spriteRender;
	GameCursor * m_gamecursor;
	AIEditNodeButton* m_aieditnodebutton;
	AIEditNodeOrder* m_aieditnodeorder;
	AIEditNodeProcess* m_aieditnodeprocess;
	AIEditNodeSelectFonts* m_aieditnodeselectfonts;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};