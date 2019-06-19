#include "stdafx.h"
#include "Act_superBeam.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_superBeam::Act_superBeam()
{
	m_ActionId = enSuperBeam;
}

bool Act_superBeam::Action(Monster* me) {
		if (m_target == nullptr and m_timer >= m_cooltime) return true;

		if (m_first) {
			if (me->GetMP() < m_cost) return true;
			m_cBeam.Fire(me, m_target, L"Assets/effect/beam/Laserbeam.efk", L"Assets/sound/bom.wav", laserRange, m_damage,m_cost);
			m_first = false;
		}
		else if (m_timer >= m_cooltime) {
			me->anim_idle();
			return true;
		}

		if (m_cBeam.DamageCalc()) m_timer += IGameTime().GetFrameDeltaTime();

		return false;
}