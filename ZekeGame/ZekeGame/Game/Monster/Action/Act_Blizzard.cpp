#include "stdafx.h"
#include "Act_Blizzard.h"
#include "../Monster.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_Blizzard::Act_Blizzard() {
	m_ActionId = enBlizzard;
}

bool Act_Blizzard::Action(Monster* me) {
	//if (m_target == nullptr) return true;
	//if (m_first) {
	//	float mp = me->GetMP();
	//	if (mp < m_cost) return true;
	//	me->anim_extra1();
	//	//auto m_efk = NewGO<CEffect>(0, "ef");
	//	//m_efk->SetScale({ 8,8,8 });
	//	//m_efk->SetPosition(m_target->Getpos());
	//	//m_efk->Play(L"Assets/effect/buff.efk");
	//	me->anim_extra1();

	//	CVector3 v = m_target->Getpos() - me->Getpos();
	//	float cta = atan2f(v.x, v.z);
	//	CQuaternion rot;
	//	rot.SetRotation(CVector3::AxisY(), cta);
	//	me->SetRotation(rot);

	//	m_efk = NewGO<CEffect>(0);
	//	m_efk->SetPosition(me->Getpos());
	//	m_efk->SetRotation(me->GetRotation());
	//	m_efk->SetScale(m_efs);
	//	m_efk->Play(L"Assets/effect/beam/Laserbeam.efk");

	//	//TODO : ‰¹‚ð•Ï‚¦‚é
	//	Sound* sound = NewGO<Sound>(0, "snd");
	//	sound->Init(L"Assets/sound/bom.wav");
	//	sound->Play();

	//	m_laserTheta = cta;

	//	m_first = false;
	//}
	//else if (!m_efk->IsPlay()) {
	//	return true;
	//}

	//if (m_efk->IsPlay()) {
	//	for (auto mon : g_mons)
	//	{
	//		if (mon == NULL)
	//			break;

	//		CVector3 vec = mon->Getpos() - me->Getpos();
	//		float currentTheta = atan2(vec.x, vec.z);
	//		float dif = max(currentTheta, m_laserTheta) - min(currentTheta, m_laserTheta);
	//		if (dif < m_near and mon != me)
	//		{
	//			mon->DamageEx(me->GetExAttack());
	//		}
	//	}
	//}
	//return false;

	//	ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
	//	actEG->init(m_efk, m_target, ACTEffectGrant::State::enDoT, 0, 0, 50);
	//	m_target->SetAbnormalState(actEG);

	//	//Sound* snd = NewGO<Sound>(0, "snd");
	//	//snd->Init(L"Assets/sound/buff.wav");
	//	//snd->SetVolume(1.2f);
	//	//snd->Play();

	//	//CVector3 v = m_target->Getpos() - me->Getpos();
	//	//float cta = atan2f(v.x, v.z);
	//	//CQuaternion rot;
	//	//rot.SetRotation(CVector3::AxisY(), cta);
	//	//me->SetRotation(rot);
	//	//m_first = false;
	//}
	//else {
	//	m_timer++;
	//	if (!me->isAnimPlay() and m_timer >= m_cooltime)
	//	{
	//		me->anim_idle();
	//		return true;
	//	}
	//}
	return false;
}