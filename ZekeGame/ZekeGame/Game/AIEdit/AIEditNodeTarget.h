#pragma once
class GameCursor;
class AIEditNodeButton;
class AIEditNode;
class AIEditNodeTechnique;
class AIEditNodeProcess;
class AIEditNodeSelectFonts;
class AIEditNodeTarget : public GameObject
{


public:

	~AIEditNodeTarget();


	bool Start();
	void Update();
	void Num();
	void Technique();
	void FontsConfirmation();

	enum target {

		enme = 100,
		enbaddy,
		enenemy,
		ennull = 0,
	};

	int GetTarget()
	{
		return m_target;
	}

	bool Getfonttarget()
	{
		return fonttarget;
	}
	

private:

	target m_target = ennull;
	std::vector<FontRender*> m_fonts;
	std::vector<FontRender*> m_font;
	int button = 3;
	bool Choice0 = false;
	bool fonttarget = false;
	bool fonts = false;
	bool contact1 = false;
	bool contact2 = false;

	CVector3 m_position = CVector3::Zero();
	CVector3 cursorpos = CVector3::Zero();

	AIEditNodeButton* m_aieditnodebutton;
	SpriteRender* m_spriteRender;
	FontRender* m_fontRender;
	GameCursor * m_gamecursor;
	AIEditNode* m_aieditnode;
	AIEditNodeTechnique* m_aieditnodetechique;
	AIEditNodeProcess* m_aieditnodeprocess;
	AIEditNodeSelectFonts* m_aieditnodeselectfonts;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};