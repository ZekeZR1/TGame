#pragma once

class GameCursor;
// THIS IS CAMERA.
class GameCamera;
class AIEditNode;
class AIEditNodeNum;

class AIEditNodeInequ : public GameObject
{

public:

	~AIEditNodeInequ();
	bool Start() override final;
	void Update() override final;
	void SetPointPos(int numx, int numy);
	void Num();

	void GetChoice2(bool a)
	{
		Choice2 = a;
	}

private:

	int button = 5;							//ボタンの数。
	bool Choice2 = false;					//何かが選択されたらtrueになる。


	SpriteRender * m_spriteRender;
	SpriteRender* sr;
	GameCursor * m_gamecursor;
	AIEditNodeNum* m_aieditnodenum;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();
	


	AIEditNode * m_aieditnode;
	std::vector<SpriteRender*> m_spriteRenders;

};