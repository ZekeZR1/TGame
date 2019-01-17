#include "stdafx.h"
#include "TestScene.h"
#include "TestScene2.h"


TestScene2::TestScene2()
{
}


TestScene2::~TestScene2()
{
}

bool TestScene2::Start() {
	return true;
}

void TestScene2::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<TestScene>(0, "TestScene");
	}
}