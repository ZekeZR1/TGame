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

	int button = 4;						//ボタンの数

	bool Choice1 = false;				//何かを選択するとtrueになる
	bool Nodefont = false;              //AIEditNodeSelectFontsで使うよ。
	bool contact1 = false;
	bool contact2 = false;              //技を選択するとtrueになる。

	CVector2 SetShadowPos = { 5.f,-5.f };

	CVector3 cursorpos = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	std::vector<FontRender*> m_font;
	std::vector<AIEditNodeButton*> m_nodebuttons;

	SpriteRender* m_spriteRender = nullptr;
	SpriteRender* sr = nullptr;

	GameCursor * m_gamecursor = nullptr;
	AIEditNodeHp * m_aieditnodehp = nullptr;
	AIEditNodeInequ* m_aieditnodeinequ = nullptr;
	AIEditNodeButton * m_aieditnodebutton = nullptr;
	AIEditNodeTechnique* m_aieditnodetechnique = nullptr;
	AIEditNodeAbnormalState* m_aieditnodeabnorimalstate = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeOrder* m_aieditnodeoreder = nullptr;
	
};