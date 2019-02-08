#pragma once
class GameCursor;
class AIEditNodeButton;
class AIEditNodeTarget : public GameObject
{


public:

	~AIEditNodeTarget();


	bool Start();
	void Update();


private:

	int button = 3;
	CVector3 m_position = CVector3::Zero();
	AIEditNodeButton* m_aieditnodebutton;
	SpriteRender* m_spriteRender;
	GameCursor * m_gamecursor;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};