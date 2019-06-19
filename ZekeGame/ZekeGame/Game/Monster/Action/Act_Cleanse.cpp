#include "stdafx.h"
#include "Act_Cleanse.h"
#include "../../GameData.h"
#include "ACTEffect.h"


Act_Cleanse::Act_Cleanse()
{
	m_ActionId = enCleanse;
}


bool Act_Cleanse::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		me->SetMP(mp - m_cost);

		me->anim_extra1();
		auto state = m_target->GetAbnormalState();
		for (auto s : state) {
			m_target->ClearAbnormalState(s);
		}

		auto eff = NewGO<CEffect>(0, "ef");
		eff->SetScale({ 4,4,4 });
		eff->SetPosition(m_target->Getpos());
		eff->Play(L"Assets/effect/heal.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(eff, m_target);

		Sound* snd = NewGO<Sound>(0, "snd");
		snd->Init(L"Assets/sound/se_maoudamashii_magical11.wav");
		snd->SetVolume(1.2f);
		snd->Play();

		CVector3 v = m_target->Getpos() - me->Getpos();

		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);

		m_first = false;
	}
	return false;
}