#include "stdafx.h"
#include "Act_Thunder.h"
#include "ACTEffect.h"
#include "../Monster.h"
#include "../../GameData.h"

Act_Thunder::Act_Thunder() {
	m_ActionId = enThunder;
}

bool Act_Thunder::Action(Monster* me) {
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
		CQuaternion er = CQuaternion::Identity();
		er.SetRotationDeg(CVector3::AxisY(), 180);
		er.Multiply(me->GetRotation());
		m_beamefk->SetRotation(er);
		m_beamefk->SetScale(m_efs);
		m_beamefk->Play(L"Assets/effect/thuder.efk");

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

	m_timer += IGameTime().GetFrameDeltaTime();

	if (!m_beamefk->IsPlay())  return false;

	for (auto mon : g_mons) {
		if (mon == nullptr or mon == me) continue;
		if (!IsHitting(mon, me)) continue;
		float dmg = me->GetExAttack() * m_damage;
		mon->DamageEx(0);
		if (m_isAbnormal[mon]) continue;
		m_timerForGrantAbs[mon] += IGameTime().GetFrameDeltaTime();
		if (m_timerForGrantAbs[mon] > m_grantAbsTime) GrantAbnormalState(mon, me);
	}

	return false;
}


void Act_Thunder::GrantAbnormalState(Monster* mon, Monster* me) {
	auto efk = NewGO<CEffect>(0);
	efk->SetPosition(me->Getpos());
	efk->SetRotation(me->GetRotation());
	efk->SetScale(m_efs);
	efk->Play(L"Assets/effect/SIBIRUD.efk");
	ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
	actEG->init(efk, mon, ACTEffectGrant::State::enHardCC, 0, 0, m_DoTEndTime, me);
	mon->SetAbnormalState(actEG);
	m_isAbnormal[mon] = true;
}

bool Act_Thunder::IsHitting(Monster* mon, Monster* me) {
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
		if (v1.Dot(v2) < 0)  isFront = false;
	}

	return LeftResult == enCLOCKWISE and RightResult == enCOUNTER_CLOCKWISE and isFront;
}