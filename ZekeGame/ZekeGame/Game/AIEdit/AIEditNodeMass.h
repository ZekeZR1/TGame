#pragma once

class AIEditNodeMass :public GameObject
{

public:

	~AIEditNodeMass();

	bool Start() override final;
	void Update() override final;

private:

	SpriteRender * m_spriteRender;

};