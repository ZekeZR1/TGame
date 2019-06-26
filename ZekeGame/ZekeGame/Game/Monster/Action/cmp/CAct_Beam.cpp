#include "stdafx.h"
#include "CAct_Beam.h"
#include "../../Monster.h"
#include "../ACTEffect.h"
#include "../../../GameData.h"

CAct_Beam::~CAct_Beam() {
	if(m_beamefk != nullptr)
		m_beamefk->Stop();
}

void CAct_Beam::Fire(Monster* me, Monster* target, const wchar_t* effectPath, const wchar_t* soundPath, float range, float baseDamage, float cost, CVector3 effectScale) {
	if (target == nullptr) return;
	RotateToTarget(me, target);
	m_beamefk = NewGO<CEffect>(0,"beamEffect");
	auto ep = me->Getpos();
	auto h = me->Getheight();
	ep.y += h / 2;
	m_beamefk->SetPosition(ep);
	CQuaternion er = CQuaternion::Identity();
	er.SetRotationDeg(CVector3::AxisY(), 180);
	er.Multiply(me->GetRotation());
	m_beamefk->SetRotation(er);
	m_beamefk->SetScale(effectScale);
	m_beamefk->Play(effectPath);

	m_se = NewGO<Sound>(0, "snd");
	m_se->Init(soundPath);
	m_se->Play();

	crs = target->Getpos() - me->Getpos();
	crs.Cross(CVector3::Up());
	crs.Normalize();
	crs *= range;
	m_targetPosition = target->Getpos();

	m_me = me;
	m_baseDamage = baseDamage;
	m_cost = cost;
}


bool CAct_Beam::DamageCalc() {
	if (m_beamefk == nullptr or !m_beamefk->IsPlay()) return true;
	if (m_me->GetMP() - m_cost <= 0) {
		m_beamefk->Stop();
		m_se->Stop();
		return true;
	}
	m_me->SetMP(m_me->GetMP() - m_cost);
	for (auto mon : g_mons) {
		if (mon == nullptr or mon == m_me) continue;
		if (!IsHitting(mon, m_me)) continue;
		float dmg = m_me->GetExAttack() * m_baseDamage;
		mon->DamageEx(dmg);
		if (m_state == ACTEffectGrant::State::enNull) continue;
		if (m_isAbnormal[mon]) continue;
		m_timerForGrantAbs[mon] += IGameTime().GetFrameDeltaTime();
		if (m_timerForGrantAbs[mon] > m_grantAbsTime)
			GrantAbnormalState(mon, m_me, m_absEfkPath, m_state, m_DoTEndTime, m_DoTDamage);
	}
	return false;
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