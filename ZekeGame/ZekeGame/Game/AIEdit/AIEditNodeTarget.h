#pragma once
class GameCursor;
class AIEditNodeButton;
class AIEditNode;
class AIEditNodeTechnique;
class AIEditNodeProcess;
class AIEditNodeTarget : public GameObject
{


public:

	~AIEditNodeTarget();


	bool Start();
	void Update();
	void Num();
	void Technique();

private:

	std::vector<FontRender*> m_fonts;
	int button = 3;
	bool Choice0;
	CVector3 m_position = CVector3::Zero();
	AIEditNodeButton* m_aieditnodebutton;
	SpriteRender* m_spriteRender;
	FontRender* m_fontRender;
	GameCursor * m_gamecursor;
	AIEditNode* m_aieditnode;
	AIEditNodeTechnique* m_aieditnodetechique;
	AIEditNodeProcess* m_aieditnodeprocess;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};