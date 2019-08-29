#include "stdafx.h"
#include "ACTEffect.h"

#include "../Monster.h"

ACTEffectGrant::~ACTEffectGrant()
{
}

void ACTEffectGrant::OnDestroy() {
	m_effect->Stop();
	//if (m_isTargetAlive and m_target != nullptr) {
		//m_target->ClearAbnormalState(this);
//	}
	puts("acteffect grant Destroy");
}

void ACTEffectGrant::init(CEffect * effect, Monster * target, int state, float dam, float time,float endTime, Monster* me,float DoTParam)
{
	m_effect = effect;
	m_target = target;

	m_state = (State)state;
	m_dam = dam;
	m_damTime = time;
	m_endTime = endTime;
	m_Invoker = me;
	m_DoTParam = DoTParam;
	if(me != nullptr)
		m_invokerExAtk = m_Invoker->GetExAttack();
	AddAct();
	printf("ACTEffect add, target is %d, me is %d state is %d\n",target->Getnum(), me->Getnum(), state);
}

void ACTEffectGrant::Update()
{
	if (m_target == nullptr or !m_isTargetAlive)
	{
		puts("target is null or dead delete");
		DeleteGO(this);
		return;
	}
	
	switch (m_state)
	{
	case enDoT:
	{
		float hp = m_target->GetHP();
		hp -= m_DoTParam * m_invokerExAtk;
		m_target->SetHP(hp);
		break;
	}
	}

	if (m_damTime < -0.00001f || m_damTime <= m_time)
	{
		switch (m_state)
		{
		case enDamage:
		{
			float HP = m_target->GetHP();
			m_target->SetHP(HP - m_dam);
			break;
			m_time = 0;
			DeleteGO(this);
			break;
		}
		}
	}
	if(m_effect->IsPlay())
		m_effect->SetPosition(m_target->Getpos());
	m_time += IGameTime().GetFrameDeltaTime() * 10;
	if (m_time >= m_endTime) {
		Clear();
	}
}

void ACTEffectGrant::SetAbnormalState(int abn)
{
	m_abnormal = abn;
	if(m_abnormal != 0)
		m_target->SetAbnormalState(this);
}


void ACTEffectGrant::AddAct() {
	switch (m_state) {
	case enCC:
	{
		m_tarSpeed = m_target->GetSpeed();
		m_target->SetSpeed(m_tarSpeed * 0.5);
		break;
	}
	case enHardCC:
	{
		m_abnormal = Monster::abStan;
		m_tarSpeed = m_target->GetSpeed();
		//m_target->SetSpeed(0);
		m_target->anim_idle();
		//m_target->stop
		break;
	}
	case enBuffAtcPow:
	{
		m_pow = m_target->GetAttack();
		m_target->SetAttackPower(m_pow * m_buffdebuffParam);
		m_ExPow = m_target->GetExAttack();
		m_target->SetAttackPower(m_ExPow * m_buffdebuffParam);
		break;
	}
	case enBuffDefPow:
	{
		m_pow = m_target->GetDefense();
		m_target->SetDefensePower(m_pow * m_buffdebuffParam);
		m_ExPow = m_target->GetExDefense();
		m_target->SetExDefense(m_ExPow * m_buffdebuffParam);
		break;
	}
	case enDebuffAtcPow:
	{
		m_pow = m_target->GetAttack();
		m_target->SetDefense(m_pow * m_buffdebuffParam);
		m_ExPow = m_target->GetExDefense();
		m_target->SetExDefensePower(m_ExPow * m_buffdebuffParam);
		break;
	}
	case enDebuffDefPow:
	{
		m_pow = m_target->GetDefense();
		m_target->SetDefense(m_pow * m_buffdebuffParam);
		m_ExPow = m_target->GetExDefense();
		m_target->SetExDefense(m_ExPow * m_buffdebuffParam);
		break;
	}
	}
}

void ACTEffectGrant::Clear() {
	switch (m_state) {
	case enCC:
	{
		m_target->SetSpeed(m_tarSpeed);
		puts("cc delete");
		DeleteGO(this);
		break;
	}
	case enHardCC: {
		//m_target->SetSpeed(m_tarSpeed);
		puts("hard cc delete");
		DeleteGO(this);
		break;
	}
	case enBuffAtcPow:
	{
		m_target->SetAttackPower(m_pow);
		m_target->SetExAttackPower(m_ExPow);
		puts("buff atc delete");
		DeleteGO(this);
		break;
	}
	case enBuffDefPow:
	{
		m_target->SetDefensePower(m_pow);
		m_target->SetExDefense(m_ExPow);
		DeleteGO(this);
		break;
	}
	case enDebuffAtcPow:
	{
		m_target->SetAttackPower(m_pow);
		m_target->SetExAttackPower(m_ExPow);
		DeleteGO(this);
		break;
	}
	case enDebuffDefPow:
	{
		m_target->SetDefensePower(m_pow);
		m_target->SetExDefense(m_ExPow);
		DeleteGO(this);
		break;
	}
	}
}