#include "stdafx.h"
#include "Act_buffDefPow.h"
#include "../MonsterAction.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_buffDefPow::Act_buffDefPow()
{
	m_ActionId = enBuffDef;
}


Act_buffDefPow::~Act_buffDefPow()
{
}


bool Act_buffDefPow::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;

		m_pow = m_target->GetDefense();
		m_target->SetDefensePower(m_pow * 1.5);
		m_ExPow = m_target->GetExDefense();
		m_target->SetExDefense(m_ExPow * 1.5);

		auto m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale({ 8,8,8 });
		m_efk->SetPosition(m_target->Getpos());
		m_efk->Play(L"Assets/effect/buff.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, m_target);

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
		if (!me->isAnimPlay() and m_timer >= 120)
		{
			m_target->SetDefensePower(m_pow);
			m_target->SetExDefense(m_ExPow);
			return true;
		}
	}
	return false;
}