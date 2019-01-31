#pragma once

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
	void PostRender() override;
private:
	SkinModelRender* m_boneModel = nullptr;
	SpriteRender* m_sp = nullptr;
	CVector3 pos = CVector3::Zero();
	GameCamera* m_camera;
	GameCamera2D* m_2dcamera;
	AnimationClip m_anim[1];
};
