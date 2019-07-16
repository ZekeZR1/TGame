#include "stdafx.h"
#include "MonsterSelectBack.h"

MonsterSelectBack::MonsterSelectBack()
{
	m_back = NewGO<SpriteRender>(0, "sp");
	m_back->Init(L"Assets/sprite/monsel_back.dds", 1280, 720);

	
	CVector2 size[2] = { {640,554} };
	CVector3 pos[2];
	pos[0] = { -620,350,0 };
	pos[1] = { 630,-310,0 };
	float scale[2] = { 1,0.8f };
	for (int i = 0; i < 2; i++)
	{
		SpriteRender* sp = NewGO<SpriteRender>(0, "sp");
		sp->Init(L"Assets/sprite/mon_roku.dds", size[0].x, size[0].y);
		sp->SetPosition(pos[i]);
		sp->SetScale(CVector3::One() * scale[i]);

		m_hexs.push_back(sp);
	}
}

void MonsterSelectBack::OnDestroy()
{
	DeleteGO(m_back);
	for (auto h : m_hexs)
	{
		DeleteGO(h);
	}
}

void MonsterSelectBack::Update()
{
	for (int i=0;i<2;i++)
	{
		m_rot[i] += m_addrot[i];
		CQuaternion q;
		q.SetRotationDeg(CVector3::AxisZ(), m_rot[i]);
		m_hexs[i]->SetRotation(q);
	}
}
