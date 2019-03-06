#pragma once

class AIEditnode;
class AIEditNodeInequ;
class AIEditNodeOrder;
class AIEditLine;
class AIEditNodeButton;
class AIEditNodeProcess;
class AIEditNodeNum : public GameObject
{
public:

	~AIEditNodeNum();

	bool Start() override final;
	void Update() override final;
	void Order();

	void GetChoice3(bool a)
	{
		Choice3 = a;
	}

	enum Num {

		en1 = 400,
		en10,
		en30,
		en50,
		en70,
		en90,
		en100,
		ennull = 0 

	};

	int GetNum()
	{

		return m_num;
	}

private:

	Num m_num = ennull;
	int button = 7;					//ボタン。
	bool Choice3 = false;				//何かが選択されたらtrueになる。

	std::vector<FontRender*> m_fonts;
	SpriteRender * m_spriteRender;
	SpriteRender * sr;
	AIEditNode * m_aieditnode;
	GameCursor * m_gamecursor;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditLine * m_aieditline;
	AIEditNodeButton* m_aieditnodebutton;
	AIEditNodeProcess* m_aieditnodeprocess;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();
	std::vector<SpriteRender*> m_spriteRenders;

	std::vector<AIEditNodeButton*> m_nodebuttons;
};