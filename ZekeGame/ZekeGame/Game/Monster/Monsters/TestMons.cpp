#include "stdafx.h"
#include "TestMons.h"
#include "../../PythonBridge/PythonBridge.h"
//#include "Monster.h"

TestMons::TestMons()
{
	m_HP = 10;
	m_MP = 10;

	m_AnimNum = 3;


	m_smr = NewGO<SkinModelRender>(0, "smr");
	m_smr->Init(L"Assets/modelData/tesEnemy2.cmo");
	m_smr->SetPosition(CVector3::Zero());
	m_smr->SetScale({ 0.3f,0.3f, 0.3f });

	m_PB = FindGO<PythonBridge>("PB");
}

bool TestMons::Start()
{
	m_smr->SetPosition(m_pos);
	m_cc.Init(70, 120, m_pos);
	return true;
}
