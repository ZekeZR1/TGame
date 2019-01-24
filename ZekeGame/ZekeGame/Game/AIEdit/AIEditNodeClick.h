#pragma once

class GameCursor;
class AIEditNode;
class AIEditNodeClick : public GameObject
{
public:

	~AIEditNodeClick();

	bool Start() override final;
	void Update() override final;

	void GetChoice0(bool a)
	{
		Choice0 = a;
	}

	CVector3 GetPosition()
	{

		return m_position;
	}

	//bool Getx()
	//{
	//	return x;
	//}

	//bool Gety()
	//{
	//	return y;
	//}

private:

	bool Choice0 = false;

	int x = -446;
	int y = 288;

	GameCursor * m_gamecursor;
	SpriteRender * m_spriteRender;
	CVector3 m_position = CVector3::Zero();
	AIEditNode* m_aieditnode;
		
};