#pragma once

class GameCursor;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeProcess;
class AIEditNodeDeleteKey : public GameObject
{

public:

	~AIEditNodeDeleteKey();

	bool Start();
	void Update();
	void deleteclick();
	void SetOrder(AIEditNodeOrder* a);



private:



	CVector3 m_position = CVector3::Zero();

	AIEditNodeOrder* m_orderpoint = nullptr;

	SpriteRender* m_spriteRender;
	GameCursor* m_gamecursor;
	AIEditNodeOrder* m_aieditnodeorder;
	AIEditLine* m_aieditline;
	AIEditNodeProcess* m_aieditnodeprocess;
	
};