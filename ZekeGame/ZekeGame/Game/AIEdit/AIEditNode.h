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
	void SetPointPos(int numx, int numy);

private:

	SpriteRender * m_spriteRender;
	GameCursor * m_gamecursor;
	CVector3 m_position = CVector3::Zero();
	CVector3 m_pointposition = CVector3::Zero();

};