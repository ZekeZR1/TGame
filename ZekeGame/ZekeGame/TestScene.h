#pragma once
#include"Engine/character/CharacterController.h"

class GameCamera;
class GameCamera2D;
class GameCursor;
class TestScene : public GameObject
{
public:
	TestScene();
	~TestScene();
	bool Start();
	void Update();
private:
	SkinModelRender* m_model = nullptr;
	SkinModelRender* m_back = nullptr;
	SpriteRender* m_sp = nullptr;
	AnimationClip m_anim[1];
	CVector3 pos = CVector3::Zero();
	SpriteRender* m_white = nullptr;
	PhysicsStaticObject m_phy;
	PhysicsStaticObject m_phy2;
	CharacterController m_charaCon;
};
