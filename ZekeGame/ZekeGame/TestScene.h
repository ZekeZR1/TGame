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
	SkinModelRender* m_skinModel;
	SkinModelRender* m_skinModel2;
	SkinModelRender* m_bg;
	GameCursor* m_cur = nullptr;
	GameCamera* m_camera;
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 pos = CVector3::Zero();
	CFont m_font;
	SpriteRender* m_sp1;
	SpriteRender* m_sp2;
	GameCamera2D* m_2dcamera;
};
