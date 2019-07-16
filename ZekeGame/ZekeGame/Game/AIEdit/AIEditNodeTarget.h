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

	int button = 3;

	bool Choice0 = false;
	bool fonttarget = false;
	bool fonts = false;
	bool contact1 = false;
	bool contact2 = false;

	CVector2 SetShadowPos = { 5.f,-5.f };    //ï∂éöÇÃâeÇÃç¿ïWÅB

	CVector3 m_position = CVector3::Zero();
	CVector3 cursorpos = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	std::vector<FontRender*> m_font;
	std::vector<AIEditNodeButton*> m_nodebuttons;

	SpriteRender* m_spriteRender = nullptr;
	FontRender* m_fontRender = nullptr;

	AIEditNodeButton* m_aieditnodebutton = nullptr; 
	GameCursor * m_gamecursor = nullptr;
	AIEditNode* m_aieditnode = nullptr;
	AIEditNodeTechnique* m_aieditnodetechique = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeSelectFonts* m_aieditnodeselectfonts = nullptr;

};