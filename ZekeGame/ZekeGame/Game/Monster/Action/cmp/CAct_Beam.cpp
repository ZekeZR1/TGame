#include "stdafx.h"
#include "CAct_Beam.h"
#include "../../Monster.h"
#include "../ACTEffect.h"
#include "../../../GameData.h"

void CAct_Beam::Fire(Monster* me, Monster* target, const wchar_t* effectPath, const wchar_t* soundPath,float range,float baseDamage, CVector3 effectScale) {

	me->anim_extra1();

	CVector3 v = target->Getpos() - me->Getpos();
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
	m_beamefk->SetScale(effectScale);
	m_beamefk->Play(effectPath);

	Sound* sound = NewGO<Sound>(0, "snd");
	sound->Init(soundPath);
	sound->Play();

	crs = target->Getpos() - me->Getpos();
	crs.Cross(CVector3::Up());
	crs.Normalize();
	crs *= range;
	m_targetPosition = target->Getpos();

	efs = effectScale;
	m_me = me;
	m_baseDamage = baseDamage;
}


bool CAct_Beam::DamageCalc() {
	if (!m_beamefk->IsPlay()) return true;

	for (auto mon : g_mons) {
		if (mon == nullptr or mon == m_me) continue;
		if (!IsHitting(mon, m_me)) continue;
		float dmg = m_me->GetExAttack() * m_baseDamage;
		mon->DamageEx(dmg);
		if (m_isAbnormal[mon]) continue;
		m_timerForGrantAbs[mon] += IGameTime().GetFrameDeltaTime();
		if (m_timerForGrantAbs[mon] > m_grantAbsTime)
			GrantAbnormalState(mon, m_me, m_absEfkPath, m_state, m_DoTEndTime,m_DoTDamage);
	}
	return false;
}

void CAct_Beam::GrantAbnormalState(
	Monster* mon,
	Monster* me,
	const wchar_t* efPath,
	ACTEffectGrant::State state,
	float endTime,
	float DoTParam) {

	auto efk = NewGO<CEffect>(0);
	efk->SetPosition(me->Getpos());
	efk->SetRotation(me->GetRotation());
	efk->SetScale(efs);
	efk->Play(efPath);
	ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
	actEG->init(efk, mon, state, 0, 0, endTime, me, DoTParam);
	mon->SetAbnormalState(actEG);
	m_isAbnormal[mon] = true;

}

bool CAct_Beam::IsHitting(Monster* mon, Monster* me) {

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