#include "stdafx.h"
#include "Monster.h"
#include "MonsterAction.h"
#include "../PythonBridge/PythonBridge.h"
#include "../../Engine/character/CharacterController.h"
//#include "MonsterAI.h"


Monster::~Monster()
{
}

bool Monster::Start()
{
	m_PB = FindGO<PythonBridge>("PB");
	return true;
}

void Monster::Update()
{
	switch (m_state)
	{
	case en_NowLoading:
		m_PB->py_exe(m_num, m_team, m_pyFile);
		if (m_actions.size() >= 1)
		{
			m_state = en_Execute;
		}
		break;
	case en_Execute:
		execute();
		Move();
		//Turn();
		break;
	}
}

void Monster::execute()
{
	if (m_actions.size() == 0)
		return;
	if (m_actions[0]->Action(this))
	{
		m_actions.erase(m_actions.begin());
	}
}

void Monster::Move()
{
	//m_cc.Execute()
	m_pos += m_movespeed;
	m_smr->SetPosition(m_pos);
}

void Monster::Turn()
{
	CVector3 NormalizedOldSpeed = m_oldmovespeed;
	CVector3 NormalizedSpeed = m_movespeed;
	NormalizedOldSpeed.Normalize();
	NormalizedSpeed.Normalize();
	float f = NormalizedOldSpeed.Dot(NormalizedSpeed);
	CQuaternion rot;
	rot.SetRotation(CVector3::AxisY(), acosf(f));
	m_rot.Multiply(rot);
	m_smr->SetRotation(rot);
}

void Monster::AddAction(MonsterAction * ma)
{
	m_actions.push_back(ma);
}

void Monster::anim_idle()
{
	if (en_idle > m_AnimNum - 1)
	{

	}
}

void Monster::anim_walk()
{
	if (en_walk > m_AnimNum - 1)
	{

	}
}

void Monster::anim_atack()
{
	if (en_atack > m_AnimNum - 1)
	{

	}
}

void Monster::anim_defense()
{
	if (en_defense > m_AnimNum - 1)
	{

	}
}

void Monster::anim_recovery()
{
	if (en_recovery > m_AnimNum - 1)
	{

	}
}
