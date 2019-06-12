#include "stdafx.h"
#include "CAct_FanShaped.h"

//void CAct_FanShaped::DamageCacl() {
//	if (m_target == nullptr)
//		return true;
//	if (m_first) {
//		float mp = me->GetMP();
//		if (mp < m_cost)
//			return true;
//		me->SetMP(mp - m_cost);
//
//		me->anim_extra1();
//
//		CVector3 v = m_target->Getpos() - me->Getpos();
//		float cta = atan2f(v.x, v.z);
//		CQuaternion rot;
//		rot.SetRotation(CVector3::AxisY(), cta);
//		me->SetRotation(rot);
//
//		m_efk = NewGO<CEffect>(0);
//		m_efk->SetPosition(me->Getpos());
//		m_efk->SetRotation(me->GetRotation());
//		m_efk->SetScale(m_efs);
//		m_efk->Play(L"Assets/effect/beam/Laserbeam.efk");
//
//		//TODO : ‰¹‚ð•Ï‚¦‚é
//		Sound* sound = NewGO<Sound>(0, "snd");
//		sound->Init(L"Assets/sound/bom.wav");
//		sound->Play();
//
//		m_laserTheta = cta;
//
//		m_first = false;
//	}
//	else if (!m_efk->IsPlay()) {
//		return true;
//	}
//
//	if (m_efk->IsPlay()) {
//		for (auto mon : g_mons)
//		{
//			if (mon == NULL)
//				break;
//
//			CVector3 vec = mon->Getpos() - me->Getpos();
//			float currentTheta = atan2(vec.x, vec.z);
//			float dif = max(currentTheta, m_laserTheta) - min(currentTheta, m_laserTheta);
//			if (dif < m_near and mon != me)
//			{
//				mon->DamageEx(me->GetExAttack());
//			}
//		}
//	}
//}