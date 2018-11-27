#pragma once

class GameCursor;
// THIS IS CAMERA.
class GameCamera;

class AIEditNode : public GameObject
{

public:

	~AIEditNode();

	bool Start() override final;
	void Update() override final;


private:

	SpriteRender * m_spriteRender;


};