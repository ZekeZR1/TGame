#include "stdafx.h"
#include "Act_Blizzard.h"
#include "../Monster.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_Blizzard::Act_Blizzard() {
	m_ActionId = enBlizzard;
}

bool Act_Blizzard::Action(Monster* me) {
	if (m_target == nullptr and m_timer >= m_cooltime) return true;

	if (m_first) {
		if (me->GetMP() < m_cost) return true;
		m_cBeam.InitAbnormalStateInfo(L"Assets/effect/KOTIKOTI.efk",ACTEffectGrant::State::enHardCC,m_efs,m_DoTEndTime,m_grantAbsTime);
		m_cBeam.Fire(me, m_target, L"Assets/effect/briza.efk", L"Assets/sound/bom.wav", laserRange,0);
		m_first = false;
	}
	else if (!me->isAnimPlay() and m_timer >= m_cooltime) {
		me->anim_idle();
		return true;
	}

	if (m_cBeam.DamageCalc()) m_timer += IGameTime().GetFrameDeltaTime();

	return false;
}
