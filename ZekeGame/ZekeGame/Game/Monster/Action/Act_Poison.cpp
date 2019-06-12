#include "stdafx.h"
#include "ACTEffect.h"
#include "Act_Poison.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_Poison::Act_Poison() {
	m_ActionId = enPoison;
}

bool Act_Poison::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		auto toTarV = m_target->Getpos() - me->Getpos();
		if (toTarV.Length() > m_SkillRange) return true;

		me->anim_extra1();
		auto ef = NewGO<CEffect>(0, "ef");
		ef->SetScale(m_efs);
		ef->SetPosition(m_target->Getpos());
		ef->Play(L"Assets/effect/poison.efk");
		auto m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale(m_efs);
		m_efk->SetPosition(m_target->Getpos());
		m_efk->Play(L"Assets/effect/DOCDOC.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, m_target, ACTEffectGrant::State::enDoT, 0, 0, 100);
		m_target->SetAbnormalState(actEG);

		Sound* snd = NewGO<Sound>(0, "snd");
		snd->Init(L"Assets/sound/buff.wav");
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
		m_timer += IGameTime().GetFrameDeltaTime();
		if (!me->isAnimPlay() and m_timer >= m_cooltime)
		{
			me->anim_idle();
			return true;
		}
	}
	return false;
}