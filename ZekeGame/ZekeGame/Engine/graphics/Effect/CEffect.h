#pragma once
#include "CEffectEngine.h"
class CEffectEngine;

class CEffect : public GameObject
{
public:
	CEffect();
	~CEffect();
	bool Start() override;
	void Update() override;
	void Render() override;
	//„„†„Š„„…„Š
	void Play(const wchar_t* filepath);
	void Stop();

	void SetPosition(const CVector3& pos) {
		m_position = pos;
	}
	void SetRotation(const CQuaternion& rot) {
		m_rotation = rot;
	}
	void SetScale(const CVector3& scale) {
		m_scale = scale;
	}
	bool IsPlay() const {
		return g_graphicsEngine->GetEffectEngine().GetEffekseerManager().GetShown(m_handle);
	}
private:
	::Effekseer::Effect*				m_effect = NULL;
	::Effekseer::Handle				m_handle = -1;
	CVector3								m_position = CVector3::Zero();
	CQuaternion						m_rotation = CQuaternion::Identity();
	CVector3								m_scale = CVector3::One();
};


