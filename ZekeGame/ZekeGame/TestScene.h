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
	SkinModelRender* m_back = nullptr;
	SpriteRender* m_sp = nullptr;
	AnimationClip m_anim[1];
	CVector3 pos = CVector3::Zero();
	SpriteRender* m_white = nullptr;
};
