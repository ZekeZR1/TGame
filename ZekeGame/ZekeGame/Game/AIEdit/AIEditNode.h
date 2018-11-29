#pragma once

class AIEditNode :public GameObject
{
public:

	~AIEditNode();

	bool Start() override final;
	void Update() override final;

private:
	SpriteRender* m_spriteRender;

};