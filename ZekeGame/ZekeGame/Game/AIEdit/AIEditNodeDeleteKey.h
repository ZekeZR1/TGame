#pragma once

class GameCursor;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeProcess;
class AIEditNodeTechnique;
class AIEditNodeDeleteKey : public GameObject
{

public:

	~AIEditNodeDeleteKey();
	void OnDestroy();

	bool Start();
	void Update();
	void deleteclick();
	void SetOrder(AIEditNodeOrder* a);

private:

	CVector3 m_position = CVector3::Zero();

	SpriteRender* m_spriteRender = nullptr;

	AIEditNodeOrder* m_orderpoint = nullptr;
	GameCursor* m_gamecursor = nullptr;
	AIEditNodeOrder* m_aieditnodeorder = nullptr;
	AIEditLine* m_aieditline = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeTechnique* m_aieditnodetechnique = nullptr;
	
};