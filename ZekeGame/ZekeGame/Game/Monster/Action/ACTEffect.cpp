#include "stdafx.h"
#include "ACTEffect.h"

#include "../Monster.h"

ACTEffectGrant::~ACTEffectGrant()
{
	
}

void ACTEffectGrant::init(CEffect * effect, Monster * target, int state, float dam, float time)
{
	m_effect = effect;
	m_target = target;

	m_state = (State)state;
	m_dam = dam;
	m_damTime = time;
}

void ACTEffectGrant::Update()
{
	if (m_target == nullptr || !m_effect->IsPlay())
	{
		DeleteGO(this);
	}

	if (m_damTime < -0.00001f || m_damTime <= m_time)
	{
		switch (m_state)
		{
		case enDamage:
			float HP = m_target->GetHP();
			m_target->SetHP(HP - m_dam);
			break;
		}
		m_time = 0;
	}
	
	
	m_effect->SetPosition(m_target->Getpos());

	m_time += IGameTime().GetFrameDeltaTime();
}
