#include "stdafx.h"
#include "Act_obstMove.h"
#include "../MonsterAction.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_ObstMove::Act_ObstMove()
{
	m_ActionId = enObstMove;
}

Act_ObstMove::~Act_ObstMove() {
}

bool Act_ObstMove::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		me->anim_extra1();
		me->SetMP(mp - m_cost);

		//TODO : Monster‚Ìó‘ÔˆÙí‚ÉˆÚ“®‘¬“x’á‰º‚ð’Ç‰Á‚·‚é
		m_enemySpeed = m_target->GetSpeed();
		m_target->SetSpeed(m_enemySpeed * 0.5);

		m_efk = NewGO<CEffect>(0, "ef");
		m_efk->SetScale({ 8,8,8 });
		m_efk->SetPosition(m_target->Getpos());
		m_efk->Play(L"Assets/effect/debuff.efk");

		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, m_target);

		Sound* snd = NewGO<Sound>(0, "snd");
		snd->Init(L"Assets/sound/debuff.wav");
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
		if (!me->isAnimPlay()and m_timer >= 120)
		{
			m_target->SetSpeed(m_enemySpeed);
			return true;
		}
	}
	return false;
}