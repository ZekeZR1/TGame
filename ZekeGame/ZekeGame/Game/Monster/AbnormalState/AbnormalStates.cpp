#include "stdafx.h"
#include "AbnormalStates.h"

#include "../Monster.h"
#include "../Action/ACTEffect.h"



void AbnormalStates::Poison(Monster* tar)
{
	CEffect* ef = NewGO<CEffect>(0, "ef");
	ef->Play(L"");
	ACTEffectGrant* aeg = NewGO<ACTEffectGrant>(0, "AEG");
	aeg->init(ef, tar, ACTEffectGrant::enDamage, 10, 1);
	aeg->SetAbnormalState(Monster::abPoison);
}

void AbnormalStates::Stan(Monster* tar)
{
	CEffect* ef = NewGO<CEffect>(0, "ef");
	ef->Play(L"");
	ACTEffectGrant* aeg = NewGO<ACTEffectGrant>(0, "AEG");
	aeg->init(ef, tar, ACTEffectGrant::enDamage, 10, 1);
	aeg->SetAbnormalState(Monster::abStan);
}

void AbnormalStates::Burn(Monster* tar)
{
	CEffect* ef = NewGO<CEffect>(0, "ef");
	ef->Play(L"");
	ACTEffectGrant* aeg = NewGO<ACTEffectGrant>(0, "AEG");
	aeg->init(ef, tar, ACTEffectGrant::enDamage, 10, 1);
	aeg->SetAbnormalState(Monster::abBurn);
}
