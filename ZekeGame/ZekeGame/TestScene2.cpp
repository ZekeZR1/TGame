#include "stdafx.h"
#include "TestScene.h"
#include "GameCamera.h"
#include "TestScene2.h"


TestScene2::TestScene2()
{
}


TestScene2::~TestScene2()
{
	DeleteGO(m_model);
}

bool TestScene2::Start() {
	m_model = NewGO<SkinModelRender>(0, "model");
	m_model->Init(L"Assets/modelData/Test.cmo");
	m_camera = NewGO<GameCamera>(0, "camera");
	return true;
}

void TestScene2::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<TestScene>(0, "TestScene");
	}
}