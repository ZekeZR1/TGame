#include "stdafx.h"
#include "TestMons.h"
#include "../../PythonBridge/PythonBridge.h"
//#include "Monster.h"

TestMons::TestMons()
{
	m_HP = 10;
	m_MP = 10;
	m_radius = 20;
	m_height = 70;

	m_AnimNum = 0;

	m_smr = NewGO<SkinModelRender>(0, "smr");
	m_smr->Init(L"Assets/modelData/tesEnemy3.cmo");
	m_smr->SetPosition(CVector3::Zero());

	

	init
	(
		10,		//HP
		10,		//MP
		10,		//hδΝ
		10,		//ΑκhδΝ
		10,		//UΝ
		10,		//ΑκUΝ
		10,		//Xs[h	
		20,		//RWΜΌa
		70,		//³
		m_smr,	//rkin lodel qender
		0		//Aj[VΜ
	);
	ActionID* ua = new ActionID[6];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enLeave;
	ua[enDefense] = enDefense;
	ua[4] = enTackle;
	ua[5] = enActNone;
	SetUseAction(ua);
	//m_PB = FindGO<PythonBridge>("PB");

	m_ID = 0;
}