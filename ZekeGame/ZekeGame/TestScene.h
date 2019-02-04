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
	SkinModelRender* m_model = nullptr;
	SpriteRender* m_sp = nullptr;
	CVector3 pos = CVector3::Zero();
	AnimationClip m_anim[1];
	SpriteRender* m_white = nullptr;
};
