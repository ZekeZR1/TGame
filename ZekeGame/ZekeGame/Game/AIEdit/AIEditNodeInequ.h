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
	void FontsConfirmation();

	enum Inequ {

		enDainari = 300,
		enShowers,
		enNull = 0,
	};

	void GetChoice2(bool a)
	{
		Choice2 = a;
	}

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
	bool contact1 = false;
	bool contact2 = false;

	CVector2 SetShadowPos = { 5.f,-5.f };

	CVector3 cursorpos = CVector3::Zero();
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<FontRender*> m_fonts;
	std::vector<FontRender*> m_font;
	std::vector<SpriteRender*> m_spriteRenders;
	std::vector<AIEditNodeButton*> m_nodebuttons;

	SpriteRender * m_spriteRender = nullptr;
	SpriteRender* sr = nullptr;

	GameCursor * m_gamecursor = nullptr;
	AIEditNodeNum* m_aieditnodenum = nullptr;
	AIEditNodeButton* m_aieditnodebutton = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr; 
	AIEditNode* m_aieditnode = nullptr;
	AIEditNodeSelectFonts* m_aieditnodeselectfont = nullptr;

};