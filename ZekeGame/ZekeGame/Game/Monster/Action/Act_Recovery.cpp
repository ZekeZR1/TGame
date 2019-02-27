#include "stdafx.h"
#include "Act_Recovery.h"

#include "../../GameData.h"
#include "ACTEffect.h"

Act_Recovery::Act_Recovery()
{
	m_ActionId = enRecovery;
}

bool Act_Recovery::Action(Monster * me)
{
	if (m_target == nullptr)
		return true;
	if (m_first)
	{
		float CMP = 0.1f;
		float mp = me->GetMP();
		if (mp < CMP)
			return true;
		me->anim_extra1();
		
		float hp = m_target->GetHP();
		//hp += 20;
		hp += 50;
		m_target->SetHP(hp);

		mp -= CMP;
		me->SetMP(mp);

		eff = NewGO<CEffect>(0, "ef");
		eff->SetScale({ 4,4,4 });
		eff->SetPosition(m_target->Getpos());
		eff->Play(L"Assets/effect/heal.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(eff, m_target);
		
		Sound* snd = NewGO<Sound>(0, "snd");
		snd->Init(L"Assets/sound/se_maoudamashii_magical11.wav");
		snd->Play();

		CVector3 v = m_target->Getpos() - me->Getpos();

		float cta = atan2f(v.x, v.y);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);

		m_first = false;
	}
	else
	{
		if (!me->isAnimPlay())
		{
			return true;
		}
	}
	return false;
}
