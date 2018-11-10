#include "stdafx.h"
#include "Monster.h"
#include "MonsterAction.h"
#include "../PythonBridge/PythonBridge.h"
#include "../../Engine/character/CharacterController.h"
//#include "MonsterAI.h"


bool Monster::Start()
{
	PythonBridge* pb = FindGO<PythonBridge>("PB");
	pb->py_exe(m_num, m_team, m_pyFile);
	return true;
}

void Monster::Update()
{
	execute();
	Move();
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
	m_pos += m_speed;
	m_smr->SetPosition(m_pos);
}

void Monster::Turn()
{
}

void Monster::AddAction(MonsterAction * ma)
{
	m_actions.push_back(ma);
}
