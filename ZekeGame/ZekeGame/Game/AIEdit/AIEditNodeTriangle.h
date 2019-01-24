#pragma once

class AIEditLine;
class AIEditNodeTriangle :public GameObject
{
public:
	~AIEditNodeTriangle();

	bool Start();
	void Update();


private:

	SpriteRender * m_spriteRender;
	AIEditLine * m_aieditline;
	CVector3 m_pos = CVector3::Zero();
};