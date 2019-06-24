#include "stdafx.h"
#include "Act_ClearStack.h"
#include "ACTEffect.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_ClearStack::Act_ClearStack() {
	m_ActionId = enClearStack;
}

bool Act_ClearStack::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		me->SetMP(mp - m_cost);

		me->anim_extra1();
		auto m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale({ 8,8,8 });
		m_efk->SetPosition(m_target->Getpos());
		m_efk->Play(L"Assets/effect/buff.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, m_target, ACTEffectGrant::State::enNull, 0, 0, 50);
		m_target->SetAbnormalState(actEG);

		m_target->ClearActionStack();

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
		if (m_timer >= m_cooltime)
		{
			me->anim_idle();
			return true;
		}
	}
	return false;
}