#include "stdafx.h"
#include "TestMons.h"
//#include "Monster.h"

TestMons::TestMons()
{
	HP = 10;
	MP = 10;
	
}

bool TestMons::Start()
{
	m_smr = NewGO<SkinModelRender>(0, "smr");
	m_smr->Init(L"Assets/modelData/tesEnemy2.cmo");
	m_smr->SetPosition(CVector3::Zero());
	m_smr->SetScale({ 0.3f,0.3f, 0.3f });
	return true;
}

void TestMons::Update()
{
}
