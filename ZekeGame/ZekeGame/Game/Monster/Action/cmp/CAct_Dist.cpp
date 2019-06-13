#include "stdafx.h"
#include "CAct_Dist.h"
#include "../../Monster.h"
#include "../ACTEffect.h"
#include "../../../GameData.h"


void CAct_Dist::Fire(Monster* me, Monster* target, const wchar_t* effectPath, const wchar_t* soundPath, float range, float baseDamage, CVector3 effectScale) {

	RotateToTarget(me, target);

	m_beamefk = NewGO<CEffect>(0);
	m_beamefk->SetPosition(target->Getpos());

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

	m_me = me;
	m_baseDamage = baseDamage;
}


bool CAct_Dist::DamageCalc() {
	if (!m_beamefk->IsPlay()) return true;

	//for (auto mon : g_mons) {
	//	if (mon == nullptr or mon == m_me) continue;
	//	if (!IsHitting(mon, m_me)) continue;
	//	float dmg = m_me->GetExAttack() * m_baseDamage;
	//	mon->DamageEx(dmg);
	//	if (m_state == ACTEffectGrant::State::enNull) continue;
	//	if (m_isAbnormal[mon]) continue;
	//	m_timerForGrantAbs[mon] += IGameTime().GetFrameDeltaTime();
	//	if (m_timerForGrantAbs[mon] > m_grantAbsTime)
	//		GrantAbnormalState(mon, m_me, m_absEfkPath, m_state, m_DoTEndTime, m_DoTDamage);
	//}
	return false;
}
