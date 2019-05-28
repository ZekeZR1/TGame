#include "stdafx.h"
#include "MonsterEffect.h"
#include "Monster.h"

MonsterEffect::~MonsterEffect()
{
	if(m_effect != nullptr)
		DeleteGO(m_effect);
}

void MonsterEffect::init(const wchar_t* path,Motion motion,Monster* me,CVector3 offset,CVector3 scale )
{
	m_effect = NewGO<CEffect>(0, "effe");
	CVector3 pos = me->Getpos() + offset;
	m_effect->SetPosition(pos);
	m_effect->Play(path);

	m_effect->SetScale(scale);
	m_scale = scale;
	
	/*CVector3 front = me->GetFrontvec();
	float ang = atan2f(front.x, front.z);
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(),ang);
	m_effect->SetRotation(rot);*/

	m_motion = motion;
	m_me = me;
	m_offset = offset;
}

void MonsterEffect::Update()
{
	if (m_effect == nullptr)
	{
		DeleteGO(this);
		return;
	}
	switch (m_motion)
	{
	case en_front:
		MFront();
		break;
	case en_rotate:
		MRotate();
		break;
	case en_left:
		MLeft();
		break;
	case en_right:
		MRight();
		break;
	}
}

void MonsterEffect::MFront()
{
	CVector3 front = m_me->GetFrontvec();
	float ang = atan2f(front.x, front.z);
	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), ang);
	m_effect->SetRotation(rot);

	CVector3 ofs = m_offset;
	ofs.Normalize();
	ofs.Cross(front);
	ofs *= m_offset.Length();

	CVector3 pos = m_me->Getpos() + ofs;
	m_effect->SetPosition(pos);
}

void MonsterEffect::MRotate()
{
}

void MonsterEffect::MLeft()
{
}

void MonsterEffect::MRight()
{
}

bool MonsterEffect::IsPlay()
{
	return m_effect->IsPlay();
}
