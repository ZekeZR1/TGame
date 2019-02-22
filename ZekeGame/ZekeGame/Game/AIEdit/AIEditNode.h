#pragma once

class GameCursor;
// THIS IS CAMERA.
class GameCamera;
class AIEditNodeHp;
class AIEditNodeInequ;
class AIEditNodeButton;
class AIEditNodeTechnique;
class AIEditNodeAbnormalState;
class AIEditNode : public GameObject
{

public:

	~AIEditNode();

	bool Start() override final;
	void Update() override final;
	void Inequ();
	void Technique();
	void Abnormal();

	void SetChoice1(bool a)
	{
		Choice1 = a;
	}

	bool GetChoice1()
	{

		return Choice1;
	}

	enum Node {

		enHp = 200,
		enMp,
		enAb,
		enNull,
	};

	int GetNode()
	{
		return m_Node;
	}
		
private:

	Node m_Node = enNull;
	int button = 3;						//É{É^ÉìÇÃêî
	bool Choice1 = false;				//âΩÇ©ÇëIëÇ∑ÇÈÇ∆trueÇ…Ç»ÇÈ
	std::vector<FontRender*> m_fonts;
	GameCursor * m_gamecursor;
	AIEditNodeHp * m_aieditnodehp;
	AIEditNodeInequ* m_aieditnodeinequ;
	SpriteRender * m_spriteRender;
	SpriteRender* sr;
	AIEditNodeButton * m_aieditnodebutton;
	AIEditNodeTechnique* m_aieditnodetechnique;
	AIEditNodeAbnormalState* m_aieditnodeabnorimalstate;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();
	CFont m_font;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};