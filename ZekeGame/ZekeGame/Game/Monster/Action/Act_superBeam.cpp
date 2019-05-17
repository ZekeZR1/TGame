#include "stdafx.h"
#include "Act_superBeam.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_superBeam::Act_superBeam()
{
	m_ActionId = enSuperBeam;
}

bool Act_superBeam::Action(Monster* me) {
	if (m_target == nullptr)
		return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost)
			return true;
		me->SetMP(mp - m_cost);

		CVector3 v = m_target->Getpos() - me->Getpos();
		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);

		m_efk = NewGO<CEffect>(0);
		m_efk->SetPosition(me->Getpos());
		m_efk->SetRotation(me->GetRotation());
		m_efk->Play(L"Assets/effect/beam/Laserbeam.efk");

		Sound* sound = NewGO<Sound>(0, "snd");
		sound->Init(L"Assets/sound/bom.wav");
		sound->Play();

		m_target->DamageEx(me->GetExAttack());

		m_first = false;
	}
	else if (!m_efk->IsPlay()) {
		return true;
	}
	return false;
}