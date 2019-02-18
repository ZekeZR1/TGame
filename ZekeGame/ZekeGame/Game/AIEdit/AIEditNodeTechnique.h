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

private:

	bool Tec = false;
	bool Choice4 = false;
	int button = 6;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	SpriteRender * m_spriteRender;
	GameCursor * m_gamecursor;
	AIEditNodeButton* m_aieditnodebutton;
	AIEditNodeOrder* m_aieditnodeorder;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};