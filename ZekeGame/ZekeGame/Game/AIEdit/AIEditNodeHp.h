#pragma once
class AIEditNode;
class GameCursor;
class AIEditNodeHp :public GameObject
{

public:

	~AIEditNodeHp();

	bool Start() override final;
	void Update() override final;
	void SetPointPos(int numx, int numy);

private:
	AIEditNode * m_aieditnode;
	SpriteRender * m_spriteRender;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();
	GameCursor * m_gamecursor;

};

