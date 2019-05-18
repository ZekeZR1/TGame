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
		m_efk->SetScale(m_efs);
		m_efk->Play(L"Assets/effect/beam/Laserbeam.efk");

		Sound* sound = NewGO<Sound>(0, "snd");
		sound->Init(L"Assets/sound/bom.wav");
		sound->Play();

		m_laserTheta = cta;

		m_first = false;
	}
	else if (!m_efk->IsPlay()) {
		return true;
	}

	if (m_efk->IsPlay()) {
		for (auto mon : g_mons)
		{
			if (mon == NULL)
				break;

			CVector3 vec = mon->Getpos() - me->Getpos();
			float currentTheta = atan2(vec.x,vec.z);
			float dif = max(currentTheta, m_laserTheta) - min(currentTheta, m_laserTheta);
			if (dif < m_nearTheta and mon != me)
			{
				mon->DamageEx(me->GetExAttack());
			}
		}
	}
	return false;
}