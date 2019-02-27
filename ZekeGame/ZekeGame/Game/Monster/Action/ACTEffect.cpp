#include "stdafx.h"
#include "ACTEffect.h"

#include "../Monster.h"

ACTEffectGrant::~ACTEffectGrant()
{
	
}

void ACTEffectGrant::init(CEffect * effect, Monster * target)
{
	m_effect = effect;
	m_target = target;
}

void ACTEffectGrant::Update()
{
	if (m_target == nullptr || !m_effect->IsPlay())
	{
		DeleteGO(this);
	}

	m_effect->SetPosition(m_target->Getpos());
}
