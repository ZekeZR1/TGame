#pragma once

class GameCursor;
// THIS IS CAMERA.
class GameCamera;
class AIEditNode;
class AIEditNodeNum;
class AIEditNodeButton;
class AIEditNodeProcess;
class AIEditNodeSelectFonts;
class AIEditNodeInequ : public GameObject
{

public:

	~AIEditNodeInequ();
	bool Start() override final;
	void Update() override final;
	void Num();

	void GetChoice2(bool a)
	{
		Choice2 = a;
	}

	enum Inequ {

		enDainari = 300,
		enShowers,
		enNull = 0,
	};

	int GetInequ()
	{
		return m_inequ;
	}

	bool Getinequfont()
	{

		return Inequfont;
	}


private:

	Inequ m_inequ = enNull;
	int button = 2;							//ボタンの数。
	bool Choice2 = false;					//何かが選択されたらtrueになる。
	bool Inequfont = false;

	std::vector<FontRender*> m_fonts;
	SpriteRender * m_spriteRender;
	SpriteRender* sr;
	GameCursor * m_gamecursor;
	AIEditNodeNum* m_aieditnodenum;
	AIEditNodeButton* m_aieditnodebutton;
	AIEditNodeProcess* m_aieditnodeprocess;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();
	AIEditNode * m_aieditnode;
	AIEditNodeSelectFonts* m_aieditnodeselectfont;
	std::vector<SpriteRender*> m_spriteRenders;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};