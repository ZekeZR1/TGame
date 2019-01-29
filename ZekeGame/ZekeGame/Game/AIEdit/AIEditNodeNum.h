#pragma once

class AIEditnode;
class AIEditNodeInequ;
class AIEditNodeOrder;
class AIEditLine;

class AIEditNodeNum : public GameObject
{
public:

	~AIEditNodeNum();

	bool Start() override final;
	void Update() override final;
	void SetPointPos(int numx, int numy);
	void Order();

	void GetChoice3(bool a)
	{
		Choice3 = a;
	}

private:

	int button = 12;					//ボタン。
	bool Choice3 = false;				//何かが選択されたらtrueになる。


	SpriteRender * m_spriteRender;
	SpriteRender * sr;
	AIEditNode * m_aieditnode;
	GameCursor * m_gamecursor;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditLine * m_aieditline;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

	std::vector<SpriteRender*> m_spriteRenders;
};