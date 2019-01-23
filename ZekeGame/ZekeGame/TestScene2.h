#pragma once
class TestScene2 : public GameObject
{
public:
	TestScene2();
	~TestScene2();
	bool Start() override;
	void Update() override;
private:
	GameCamera* m_camera;
	SkinModelRender* m_model;
};
