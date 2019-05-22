#include "stdafx.h"
#include "ACTEffect.h"

#include "../Monster.h"

ACTEffectGrant::~ACTEffectGrant()
{
	if (m_abnormal != Monster::abNull)
	{
		m_target->ClearAbnormalState(this);
	}
}

void ACTEffectGrant::init(CEffect * effect, Monster * target, int state, float dam, float time,float endTime)
{
	m_effect = effect;
	m_target = target;

	m_state = (State)state;
	m_dam = dam;
	m_damTime = time;
	m_endTime = endTime;
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
	
	if (m_time >= m_endTime) {

	}
	
	m_effect->SetPosition(m_target->Getpos());

	m_time += IGameTime().GetFrameDeltaTime();
}

void ACTEffectGrant::SetAbnormalState(int abn)
{
	m_abnormal = abn;
	if(m_abnormal != 0)
		m_target->SetAbnormalState(this);

}
