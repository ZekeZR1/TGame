#pragma once

class AIEditNode;
class AIEditNodeOrder;
class AIEditLine : public GameObject
{

public:

	~AIEditLine();

	bool Start() override final;
	void Update() override final;

	CVector3 GetPos()
	{

		return m_pos;
	}

private:

	int x = 50;
	bool Choice1 = false;
	CVector3 m_pos = CVector3::Zero();
	SpriteRender * m_spriteRender;
	AIEditNodeOrder * m_aieditnodeorder;
	AIEditNode * m_aieditnode;

};