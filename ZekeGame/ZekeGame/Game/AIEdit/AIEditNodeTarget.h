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

	enum target {

		enme = 100,
		enbaddy,
		enenemy,
		entechnique,
		ennull,
	};

	int GetTarget()
	{
		return m_target;
	}
	

private:

	target m_target = ennull;
	std::vector<FontRender*> m_fonts;
	int button = 4;
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