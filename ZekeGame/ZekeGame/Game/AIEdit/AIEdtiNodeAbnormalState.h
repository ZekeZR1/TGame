#pragma once

class GameCursor;
class AIEditNodeButton;
class AIEditNodeAbnormalState : public GameObject
{

public:
	~AIEditNodeAbnormalState();

	bool Start();
	void Update();


private:

	int button = 4;

	GameCursor* m_gamecursor;
	SpriteRender* m_spriteRender;
	AIEditNodeButton* m_aieditnodebutton;

	CVector3 m_position = CVector3::Zero();

	std::vector<AIEditNodeButton*> m_nodebuttons;
	

};