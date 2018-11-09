#include "stdafx.h"
#include "Monster.h"
#include "MonsterAction.h"
#include "../../Engine/character/CharacterController.h"
//#include "MonsterAI.h"


void Monster::Update()
{
}

void Monster::execute()
{
	if (m_actions.size() == 0)
		return;
	if (m_actions[0]->Action())
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
