#include "stdafx.h"
#include "IAct.h"
#include "../../Monster.h"
#include "../ACTEffect.h"
#include "../../../GameData.h"

void IAct::GrantAbnormalState(
	Monster* target,
	Monster* me,
	const wchar_t* effectPath,
	ACTEffectGrant::State state,
	float endTime,
	float DoTParam) {

	auto efk = NewGO<CEffect>(0,"ef");
	efk->SetScale(efs);
	efk->Play(m_absEfkPath);

	ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
	actEG->init(efk, target, state, 0, 0, endTime, me, DoTParam);
	target->SetAbnormalState(actEG);
	m_isAbnormal[target] = true;
}
//
//void IAct::RotateToTarget(Monster* me, Monster* target) {
//	CVector3 v = target->Getpos() - me->Getpos();
//	float cta = atan2f(v.x, v.z);
//	CQuaternion rot;
//	rot.SetRotation(CVector3::AxisY(), cta);
//	me->SetRotation(rot);
//}
//
//void IAct::GrantAbnormalState(Monster* mon, Monster* me, const wchar_t* effectPath, ACTEffectGrant::State state, float endTime, float DoTParam) {
//	auto efk = NewGO<CEffect>(0);
//	efk->SetPosition(me->Getpos());
//	efk->SetRotation(me->GetRotation());
//	efk->SetScale(m_efs);
//	efk->Play(effectPath);
//	ACTEffectGrant* actEG = NewGO<ACTEffectGrant>(0, "actEG");
//	actEG->init(efk, mon, state, 0, 0, endTime, me, DoTParam);
//	mon->SetAbnormalState(actEG);
//	m_isAbnormal[mon] = true;
//}