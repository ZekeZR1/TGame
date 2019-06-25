#include "stdafx.h"
#include "Act_Blizzard.h"
#include "../Monster.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_Blizzard::Act_Blizzard() {
	m_ActionId = enBlizzard;
}

Act_Blizzard::~Act_Blizzard() {
}

bool Act_Blizzard::Action(Monster* me) {
	if (m_target == nullptr and m_timer >= m_cooltime) return true;

	if (m_first) {
		if (me->GetMP() < m_cost) return true;
		me->SetMP(me->GetMP() - m_cost);
		m_cBeam.InitAbnormalStateInfo(L"Assets/effect/KOTIKOTI.efk",ACTEffectGrant::State::enHardCC,m_efs,m_DoTEndTime,m_grantAbsTime, m_DoTDamageParam);
		m_cBeam.Fire(me, m_target, L"Assets/effect/briza.efk", L"Assets/sound/blizzard.wav", laserRange, m_damage,m_cost);
		m_first = false;
	}
	else if (m_timer >= m_cooltime) {
		me->anim_idle();
		return true;
	}

	if (m_cBeam.DamageCalc()) m_timer += IGameTime().GetFrameDeltaTime();

	return false;
}
