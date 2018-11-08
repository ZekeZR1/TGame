#include "stdafx.h"
#include "TestMons.h"
#include "../PythonBridge/PythonBridge.h"
//#include "Monster.h"

TestMons::TestMons()
{
	m_HP = 10;
	m_MP = 10;
	m_useActionList.push_back(0);
}

bool TestMons::Start()
{
	m_smr = NewGO<SkinModelRender>(0, "smr");
	m_smr->Init(L"Assets/modelData/tesEnemy2.cmo");
	m_smr->SetPosition(CVector3::Zero());
	m_smr->SetScale({ 0.3f,0.3f, 0.3f });

	PythonBridge* pb = FindGO<PythonBridge>("PB");
	pb->py_exe(this);
	return true;
}

void TestMons::Update()
{
}
