#pragma once
class GameCursor;
class GameCamera;

class AIEditNodeButton;
class AIEditNodeOrder;
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
		encCase,
		enProtect,
		enHeel,
		enSpecial1,
		enSpecial2,
		ennull,
	};

	int Gettechnique()
	{

		return m_technique;
	}

private:

	Technique m_technique = ennull;
	bool Tec = false;
	bool Choice4 = false;
	int button = 7;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	SpriteRender * m_spriteRender;
	GameCursor * m_gamecursor;
	AIEditNodeButton* m_aieditnodebutton;
	AIEditNodeOrder* m_aieditnodeorder;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};