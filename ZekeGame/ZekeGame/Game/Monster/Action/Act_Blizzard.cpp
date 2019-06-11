#include "stdafx.h"
#include "Act_Blizzard.h"
#include "../Monster.h"
#include "ACTEffect.h"
#include "../../GameData.h"

Act_Blizzard::Act_Blizzard() {
	m_ActionId = enBlizzard;
}

bool Act_Blizzard::Action(Monster* me) {
	if (m_target == nullptr) return true;
	if (m_first) {
		float mp = me->GetMP();
		if (mp < m_cost) return true;
		me->anim_extra1();

		CVector3 v = m_target->Getpos() - me->Getpos();
		float cta = atan2f(v.x, v.z);
		CQuaternion rot;
		rot.SetRotation(CVector3::AxisY(), cta);
		me->SetRotation(rot);

		m_beamefk = NewGO<CEffect>(0);
		m_beamefk->SetPosition(me->Getpos());
		m_beamefk->SetRotation(me->GetRotation());
		m_beamefk->SetScale(m_efs);
		m_beamefk->Play(L"Assets/effect/beam/Laserbeam.efk");

		m_efk = NewGO<CEffect>(0);
		m_efk->SetPosition(me->Getpos());
		m_efk->SetRotation(me->GetRotation());
		m_efk->SetScale(m_efs);
		m_efk->Play(L"Assets/effect/beam/buff.efk");
		
		ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
		actEG->init(m_efk, m_target, ACTEffectGrant::State::enDoT, 0, 0, 50,me);
		m_target->SetAbnormalState(actEG);

		//TODO : 音を変える
		Sound* sound = NewGO<Sound>(0, "snd");
		sound->Init(L"Assets/sound/bom.wav");
		sound->Play();
		m_first = false;

		crs = m_target->Getpos() - me->Getpos();
		crs.Cross(CVector3::Up());
		crs.Normalize();
		crs *= laserRange;
		m_targetPosition = m_target->Getpos();
	}
	else if (!me->isAnimPlay() and m_timer >= m_cooltime) {
		me->anim_idle();
		return true;
	}

	CLOCKWISE LeftResult, RightResult;

	if (m_beamefk->IsPlay()) {
		for (auto mon : g_mons) {
			if (mon == nullptr) continue;
			CLOCKWISE LeftResult, RightResult;
			//左端より右か
			{
				auto LeftMyPos = me->Getpos() + crs;
				auto LeftTarPos = m_targetPosition + crs;
				auto leftV = LeftTarPos - LeftMyPos;
				auto toAnotherVfromLeft = mon->Getpos() - LeftMyPos;
				LeftResult = CVector3::ccw(leftV, toAnotherVfromLeft);
			}
			//右端より左か
			{
				auto RightMyPos = me->Getpos() - crs;
				auto RightTarPos = m_targetPosition - crs;
				auto rightV = RightTarPos - RightMyPos;
				auto toAnotherVfromRight = mon->Getpos() - RightMyPos;
				RightResult = CVector3::ccw(rightV, toAnotherVfromRight);
			}
			//技を撃ってるモンスターより前側か
			bool isFront = true;
			{
				auto v1 = m_targetPosition - me->Getpos();
				auto v2 = mon->Getpos() - me->Getpos();
				if (v1.Dot(v2) < 0) {
					isFront = false;
				}
			}
			//当たってる
			if (LeftResult == enCLOCKWISE and RightResult == enCOUNTER_CLOCKWISE and isFront) {
				if (mon != me) {
					mon->DamageEx(0.00001);
				}
			}
		}
	}
	return false;
}