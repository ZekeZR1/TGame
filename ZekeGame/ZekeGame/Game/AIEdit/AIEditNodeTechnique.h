#pragma once
class GameCursor;
class GameCamera;

class AIEditNodeButton;
class AIEditNodeOrder;
class AIEditNodeProcess;
class AIEditNodeSelectFonts;
class AIEditNodeDeleteKey;
class AIEditNodeTechnique : public GameObject
{

public:

	~AIEditNodeTechnique();

	bool Start();
	void Update();
	void Order();
	void FontsConfirmation();

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

	int button = 7;
	int techniquefont = false;

	bool Tec = false;
	bool Choice4 = false;
	bool contact1 = false;
	bool contact2 = false;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	std::vector<FontRender*> m_font;
	std::vector<AIEditNodeButton*> m_nodebuttons;

	SpriteRender * m_spriteRender = nullptr;

	GameCursor * m_gamecursor = nullptr;
	AIEditNodeButton* m_aieditnodebutton = nullptr;
	AIEditNodeOrder* m_aieditnodeorder = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeSelectFonts* m_aieditnodeselectfonts = nullptr;
	AIEditNodeDeleteKey* m_aieditnodedeletekey = nullptr;

};