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
		10,		//防御力
		10,		//特殊防御力
		10,		//攻撃力
		10,		//特殊攻撃力
		10,		//スピード	
		20,		//コリジョンの半径
		70,		//高さ
		m_smr,	//Ｓkin Ｍodel Ｒender
		0		//アニメーションの数
	);
	//m_PB = FindGO<PythonBridge>("PB");

	m_ID = 0;
}