#pragma once

class AIEditLine : public GameObject
{

public:

	~AIEditLine();

	bool Start() override final;
	void Update() override final;

private:

	SpriteRender * m_spriteRender;

};