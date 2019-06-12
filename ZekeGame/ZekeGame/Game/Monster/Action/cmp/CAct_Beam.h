#pragma once
#include "..//ACTEffect.h"
#include "IAct.h"
class Monster;

class CAct_Beam
{
public:
	void InitAbnormalStateInfo(const wchar_t* effectPath,
		ACTEffectGrant::State state,
		CVector3 effectScale,
		float DoTTime,
		float GrantAbsTime,
		float DoTDamageParam = 0.f
	) {
		wcscpy(m_absEfkPath, effectPath);
		m_DoTEndTime = DoTTime;
		m_DoTDamage = DoTDamageParam;
		m_grantAbsTime = GrantAbsTime;
		m_state = state;
		efs = effectScale;
	};

	void Fire(
		Monster* me,
		Monster* target,
		const wchar_t* beamEffectPath,
		const wchar_t* soundPath,
		float range,
		float baseDamage,
		CVector3 effectScale = { 3.5,3.5,3.5 }
	);

	//ダメージを与え終わったらtrueを返します
	bool DamageCalc();

	void GrantAbnormalState(Monster* target, Monster* me, const wchar_t* effectPath, ACTEffectGrant::State state, float endTime, float DoTParam);

private:
	bool IsHitting(Monster* mon, Monster* me);
	CEffect* m_beamefk = nullptr;
	CVector3 crs = CVector3::Zero();
	CVector3 m_targetPosition = CVector3::Zero();
	Monster* m_me = nullptr;
	CVector3 efs = CVector3::One();
	std::map<Monster*, bool> m_isAbnormal;
	std::map<Monster*, float> m_timerForGrantAbs;
	float m_DoTEndTime = 0;
	float m_baseDamage = 0;
	float m_DoTDamage = 0;
	wchar_t m_absEfkPath[256];
	float m_grantAbsTime = 0;
	ACTEffectGrant::State m_state = ACTEffectGrant::State::enNull;
};

