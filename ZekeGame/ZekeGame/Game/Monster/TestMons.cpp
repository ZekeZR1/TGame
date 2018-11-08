#include "stdafx.h"
#include "TestMons.h"
#include "../PythonBridge/PythonBridge.h"
//#include "Monster.h"

TestMons::TestMons()
{
	m_HP = 10;
	m_MP = 10;
	
}

bool TestMons::Start()
{
	m_smr = NewGO<SkinModelRender>(0, "smr");
	m_smr->Init(L"Assets/modelData/tesEnemy2.cmo");
	m_smr->SetPosition(CVector3::Zero());
	m_smr->SetScale({ 0.3f,0.3f, 0.3f });
	m_smr->SetPosition(m_pos);
	PythonBridge* pb = FindGO<PythonBridge>("PB");
	
	pb->py_exe(m_num,m_team,m_pyFile);
	return true;
}

void TestMons::Update()
{
}
