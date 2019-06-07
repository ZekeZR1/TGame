#include "stdafx.h"
#include "Act_ManaHeal.h"
#include "ACTEffect.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_ManaHeal::Act_ManaHeal() {
	m_ActionId = enManaHeal;
}

bool Act_ManaHeal::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;

		me->anim_extra1();
		{
			float mp = m_target->GetMP();
			float mxmp = m_target->GetMaxHP();
			if(mp + healParam >= mxmp)
				m_target->SetMP(mxmp);
			else
				m_target->SetMP(mp + healParam);
		}
		auto m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale({ 8,8,8 });
		m_efk->SetPosition(m_target->Getpos());
		m_efk->Play(L"Assets/effect/buff.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, m_target, ACTEffectGrant::State::enNull, 0, 0, 50);
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
		m_timer++;
		if (!me->isAnimPlay() and m_timer >= m_cooltime)
		{
			me->anim_idle();
			return true;
		}
	}
	return false;
}