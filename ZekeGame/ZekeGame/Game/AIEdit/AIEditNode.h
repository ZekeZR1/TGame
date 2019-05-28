#pragma once

class GameCursor;
// THIS IS CAMERA.
class GameCamera;
class AIEditNodeHp;
class AIEditNodeInequ;
class AIEditNodeButton;
class AIEditNodeTechnique;
class AIEditNodeAbnormalState;
class AIEditNodeProcess;
class AIEditNodeOrder;
class AIEditNode : public GameObject
{

public:

	~AIEditNode();

	bool Start() override final;
	void Update() override final;
	void Inequ();
	void Technique();
	void Abnormal();
	void FontsConfirmation();

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
		enTechnique,
		enNull = 0,
	};

	int GetNode()
	{
		return m_Node;
	}

	bool Getnodefont()
	{
		return Nodefont;
	}
		
private:

	Node m_Node = enNull;
	int button = 4;						//É{É^ÉìÇÃêî
	bool Choice1 = false;				//âΩÇ©ÇëIëÇ∑ÇÈÇ∆trueÇ…Ç»ÇÈ
	bool Nodefont = false;
	bool contact1 = false;
	bool contact2 = false;
	CVector3 cursorpos;

	std::vector<FontRender*> m_fonts;
	std::vector<FontRender*> m_font;

	GameCursor * m_gamecursor;
	AIEditNodeHp * m_aieditnodehp;
	AIEditNodeInequ* m_aieditnodeinequ;
	SpriteRender * m_spriteRender;
	SpriteRender* sr;
	AIEditNodeButton * m_aieditnodebutton;
	AIEditNodeTechnique* m_aieditnodetechnique;
	AIEditNodeAbnormalState* m_aieditnodeabnorimalstate;
	AIEditNodeProcess* m_aieditnodeprocess;
	AIEditNodeOrder* m_aieditnodeoreder;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<AIEditNodeButton*> m_nodebuttons;
};