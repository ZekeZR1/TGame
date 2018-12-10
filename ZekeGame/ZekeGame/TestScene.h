#pragma once
class TestScene : public GameObject
{
public:
	TestScene();
	~TestScene();
	bool Start();
	void Update();
private:
	SkinModelRender* m_skinModel;
	GameCamera* m_camera;
};
