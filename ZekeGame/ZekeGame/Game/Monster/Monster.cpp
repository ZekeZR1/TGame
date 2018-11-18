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
	DeleteGO(m_PB);
}

bool Monster::Start()
{
	m_smr->SetPosition(m_pos);
	m_cc.Init(m_radius, m_height, m_pos);
	m_PB = NewGO<PythonBridge>(0,"PB");
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
		if (m_time > 1)
		{
			//m_PB->py_exe(m_num, m_team, m_pyFile);
			if (!isLoading)
			{
				m_PB->py_exe(m_num, m_team, m_pyFile);
				isLoading = true;
			}
			if (m_actions.size() >= 1)
			{
				m_state = en_Execute;
				isLoading = false;
			}
			m_time = 0;
		}
		break;
	case en_Execute:
		if(!m_isKnockback)
			execute();
		break;
	case en_Dead:
		break;
	}
	Move();
	m_time += IGameTime().GetFrameDeltaTime();
}

void Monster::execute()
{
	if (m_actions.size() == 0)
	{
		m_state = en_NowLoading;
		m_time = 0;
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
	CVector3 move = m_movespeed + m_vKnockback;
	move *= 50;
	m_pos = m_cc.Execute(IGameTime().GetFrameDeltaTime(), move);
	
	
	m_smr->SetPosition(m_pos);
	if (m_isKnockback)
	{
		Knockback();
	}
	else
	{
		Turn();
	}
}

void Monster::Turn()
{
	if (m_movespeed.Length() < 0.0001f)
		return;
	float angle = atan2(m_movespeed.x, m_movespeed.z);
	m_rot.SetRotation(CVector3::AxisY(), angle);
	m_smr->SetRotation(m_rot);
}

void Monster::StartKnockback(CVector3 v)
{
	m_vKnockback = v;
	m_vSubKnock = v / 3;
	m_isKnockback = true;
}

void Monster::Knockback()
{
	
	if (m_vKnockback.Length() < 0.001f)
	{
		if (m_vSubKnock.Length() < 0.05f)
		{
			m_vKnockback = CVector3::Zero();
			m_vSubKnock = CVector3::Zero();
			m_isKnockback = false;
		}
	}
	else
	{
		m_vKnockback -= m_vSubKnock;
		m_vSubKnock /= 1.5f;
	}
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
