#include "stdafx.h"
#include "Act_Ignite.h"
#include "../Monster.h"
#include "../../GameData.h"
#include "ACTEffect.h"

Act_Ignite::Act_Ignite() {
	m_ActionId = enIgnite;
}

bool Act_Ignite::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		me->SetMP(mp - m_cost);

		auto toTarV = m_target->Getpos() - me->Getpos();
		if (toTarV.Length() > m_SkillRange) return true;

		me->anim_extra1();
		auto ef = NewGO<CEffect>(0, "ef");
		ef->SetScale(m_efs);
		ef->SetPosition(m_target->Getpos());
		ef->Play(L"Assets/effect/moyashi.efk");
		auto m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale(m_efs);
		m_efk->SetPosition(m_target->Getpos());
		m_efk->Play(L"Assets/effect/YKD.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, m_target, ACTEffectGrant::State::enDoT, 0, 0, 100,me,0);
		m_target->SetAbnormalState(actEG);

		Sound* snd = NewGO<Sound>(0, "snd");
		snd->Init(L"Assets/sound/fire2.wav");
		snd->SetVolume(1.2f);
		snd->Play();

		CVector3 v = m_target->Getpos() - me->Getpos();
		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);
		m_first = false;
	}
	else {
		m_timer+= IGameTime().GetFrameDeltaTime();
		if (m_timer >= m_cooltime)
		{
			me->anim_idle();
			return true;
		}
	}
	return false;
}