#pragma once
class GameCursor;
class GameCamera;

class AIEditNodeButton;
class AIEditNodeTechnique : public GameObject
{

public:

	~AIEditNodeTechnique();


	bool Start();
	void Update();


private:

	int button = 6;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	SpriteRender * m_spriteRender;
	GameCursor * m_gamecursor;
	AIEditNodeButton* m_aieditnodebutton;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};