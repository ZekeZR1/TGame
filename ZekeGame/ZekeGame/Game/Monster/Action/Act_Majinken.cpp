#include "stdafx.h"
#include "Act_Majinken.h"
#include "ACTEffect.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_Majinken::Act_Majinken() {
	m_ActionId = enMajinken;
}

bool Act_Majinken::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		knock = m_target->Getpos() - me->Getpos();
		CVector3 v = m_target->Getpos() - me->Getpos();
		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);

		m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale(CVector3::One() * 3.5);
		m_efk->SetPosition(me->Getpos());
		m_efk->Play(L"Assets/effect/majinken_wiat.efk");
		m_first = false;
	}
	if (m_timer >= m_chargeTime and !m_attacked) {
		float len = (m_target->Getpos() - me->Getpos()).Length();
		float mil = m_target->Getradius() + me->Getradius() + 30;
		if (len <= mil) {
			m_efk->Stop();
			auto efk = NewGO<CEffect>(0, "ef");
			efk->SetScale(CVector3::One() * 2);
			efk->SetPosition(me->Getpos());
			efk->Play(L"Assets/effect/majinken_attack.efk");
			knock.Normalize();
			knock *= 300;
			m_target->StartKnockback(knock);
			//float dam = m_damagePow * me->GetExAttack() * 1 / m_target->GetExDefense();
			m_target->Damage(10);
			m_attacked = true;
			Sound* se = NewGO<Sound>(0, "snd");
			se->Init(L"Assets/sound/punch-high2.wav");
			se->Play();
		}
		else {
			return true;
		}
	}
	if (m_timer >= m_cooltime and !me->isAnimPlay() and m_attacked) {
		me->anim_idle();
		return true;
	}
	m_timer += 60 * IGameTime().GetFrameDeltaTime();
	return false;
}