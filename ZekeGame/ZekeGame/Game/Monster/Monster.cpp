#include "stdafx.h"
#include "Monster.h"
#include "MonsterAction.h"
#include "../PythonBridge/PythonBridge.h"
#include "../../Engine/character/CharacterController.h"

#include "../GameData.h"
//#include "MonsterAI.h"


Monster::~Monster()
{
	DeleteGO(m_smr);
}

bool Monster::Start()
{
	m_PB = FindGO<PythonBridge>("PB");
	return true;
}

void Monster::Update()
{
	if (m_HP <= 0)
	{
		m_state = en_Dead;
		GameData* gd = new GameData();
		gd->deletemons(this);
		delete gd;
		DeleteGO(this);
	}
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
		Turn();
		break;
	case en_Dead:
		break;
	}
}

void Monster::execute()
{
	if (m_actions.size() == 0)
	{
		m_state = en_NowLoading;
		return;
	}
	if (m_actions[0]->Action(this))
	{
		DeleteGO(m_actions[0]);
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
	float angle = atan2(m_movespeed.x, m_movespeed.z);
	m_rot.SetRotation(CVector3::AxisY(), angle);
	m_smr->SetRotation(m_rot);
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
