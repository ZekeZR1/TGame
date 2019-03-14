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
	SkinModelRender* m_modell = nullptr;
	SkinModelRender* m_back = nullptr;
	SkinModelRender* m_mimic = nullptr;
	SkinModelRender* m_mo2 = nullptr;
	SpriteRender* m_sp = nullptr;
	AnimationClip m_anim[1];
	CVector3 pos = CVector3::Zero();
	CVector3 pos2 = { 0.f,0.f,-400.f };
	CQuaternion m_rot = CQuaternion::Identity();
	SpriteRender* m_white = nullptr;
	PhysicsStaticObject m_phy;
	PhysicsStaticObject m_phy2;
	CharacterController m_charaCon;
	CharacterController m_charaCon2;
};
