#include "stdafx.h"
#include "Win.h"
#include "../ResultCamera.h"

#include "../../Monster/Monster.h"
#include "../../GameData.h"

Win::Win(int team)
{
	m_cam = NewGO<ResultCamera>(0, "rescam");
	m_cam->SetPos({ 0,30,500 });
	m_cam->SetTar(CVector3::Zero());
	m_team = team;
	MonsterSet();
	CameraSet();

	SpriteRender* sr = NewGO<SpriteRender>(0, "sr");
	sr->Init(L"Assets/Sprite/clear.dds", 1280, 720);
}

Win::Win()
{

}

Win::~Win()
{
	DeleteGO(m_cam);
}

void Win::init(int team)
{
	m_cam = NewGO<ResultCamera>(0, "rescam");
	m_cam->SetPos({ 0,30,500 });
	m_cam->SetTar(CVector3::Zero());
	m_team = team;
	MonsterSet();
	CameraSet();

	SpriteRender* sr = NewGO<SpriteRender>(0, "sr");
	sr->Init(L"Assets/Sprite/clear.dds", 1280, 720);
}

bool Win::Start()
{

	return true;
}

void Win::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		
	}
}

void Win::MonsterSet()
{
	std::vector<Monster*> mons;
	for (auto mon : g_mons)
	{
		if (mon == NULL)
			break;
		if (mon->Getteam() == m_team)
		{
			mons.push_back(mon);
		}
	}
	CVector3 pos = CVector3::Zero();
	for (int i = 0; i < mons.size(); i++)
	{
		CVector3 add = { 30,0,0 };
		pos += add * i;
		mons[i]->Setpos(pos);
		mons[i]->SetRotation(CQuaternion::Identity());
	}
}

void Win::CameraSet()
{
}
