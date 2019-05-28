#include "stdafx.h"
#include "Act_Fire.h"
#include "../MonsterAction.h"

#include "../Monster.h"
#include "../../GameData.h"

Act_Fire::Act_Fire()
{
	m_effect = NewGO<CEffect>(0, "eff");
	m_ActionId = enFire;
}

bool Act_Fire::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;
	if (m_first)
	{
		me->anim_extra1();

		float mp = me->GetMP();
		if (mp < 20)
			return true;
		mp -= 20;
		me->SetMP(mp);

		m_pos = m_target->Getpos();

		/*CVector3 sc = CVector3::One();
		sc *= 5;*/
		m_effect->SetScale(m_efs);
		m_effect->SetPosition(m_pos);
		m_effect->Play(L"Assets/effect/fire1/fire1.efk");

		Sound* sound = NewGO<Sound>(0, "snd");
		sound->Init(L"Assets/sound/bom.wav");
		sound->Play();

		CVector3 v = m_target->Getpos() - me->Getpos();
		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);

		m_first = false;
	}
	else if (!m_effect->IsPlay())
	{
		me->anim_idle();
		return true;
	}
	
	if (m_effect->IsPlay())
	{
		for (auto mon : g_mons)
		{
			if (mon == NULL)
				break;
			CVector3 len = m_pos - mon->Getpos();
			if (len.Length() < 6*m_efs.x)
			{
				mon->DamageEx(me->GetExAttack());
			}
		}
		m_efs += {0.02f, 0.02f, 0.02f};
		m_effect->SetScale(m_efs);
	}
	
	return false;
}
