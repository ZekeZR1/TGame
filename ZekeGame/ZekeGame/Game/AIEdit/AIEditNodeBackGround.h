#pragma once

class AIEditNodeBackGround : public GameObject
{

public:

	~AIEditNodeBackGround();

	bool Start();
	void Update();


private:

	int num = 9;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_pos = CVector3::Zero();

	std::vector<FontRender*> m_fonts;

	SpriteRender* m_spriteRender = nullptr;


};