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
		INT_MAX,		//MP
		10,		//–hŒä—Í
		10,		//“Áê–hŒä—Í
		10,		//UŒ‚—Í
		10,		//“ÁêUŒ‚—Í
		10,		//ƒXƒs[ƒh
		20,		//ƒRƒŠƒWƒ‡ƒ“‚Ì”¼Œa
		120,		//‚‚³
		m_smr,	//‚rkin ‚lodel ‚qender
		0		//ƒAƒjƒ[ƒVƒ‡ƒ“‚Ì”
	);
	ActionID* ua = new ActionID[99];
	ua[enAtack] = enAtack;
	ua[enChase] = enChase;
	ua[enLeave] = enLeave;
	ua[enDefense] = enDefense;
	ua[4] = enTackle;
	ua[5] = enActNone;
	ua[6] = enSuperBeam;
	ua[7] = enObstMove;
	ua[8] = enCleanse;
	ua[9] = enBuffAtc;
	ua[10] = enDebuffAtc;
	ua[11] = enBuffDef;
	ua[12] = enDebuffDef;
	SetUseAction(ua,99);
	//m_PB = FindGO<PythonBridge>("PB");

	m_ID = 0;
}