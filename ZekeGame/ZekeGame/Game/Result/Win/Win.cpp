#include "stdafx.h"
#include "Win.h"
#include "../ResultCamera.h"

#include "../../Game.h"
#include "../../Title/pvpModeSelect.h"
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
	NewGO<PvPModeSelect>(0, "pvp");
	DeleteGO(m_sr);
	DeleteGO(m_cam);
	DeleteGO(m_srteam);
	DeleteGO(m_srwin);
	DeleteGO(FindGO<Game>("Game"));
}

void Win::init(int team)
{
	m_cam = NewGO<ResultCamera>(0, "rescam");

	m_firstpos = { -350,10,500 };
	m_firsttar = { 0,30,0 };

	m_cam->SetPos(m_firstpos);
	m_cam->SetTar(m_firsttar);

	switch (g_mons[0]->GetID())
	{
	case enTest:
		m_lastpos = { -35,50,50 };
		m_lasttar = { 0,55,0 };
		break;
	case enUmataur:
		m_lastpos = { -20,150,72 };
		m_lasttar = { 30,165,0 };
		break;
	}

	m_addpos = (m_lastpos - m_firstpos) / 8.0f;
	m_addtar = (m_lasttar - m_firsttar) / 8.0f;

	m_team = team;
	MonsterSet();
	CameraSet();

	//m_sr = NewGO<SpriteRender>(0, "sr");
	//m_sr->Init(L"Assets/Sprite/clear.dds", 1280, 720);

	
}

bool Win::Start()
{

	return true;
}

void Win::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		DeleteGO(this);
	}

	if (m_cmove)
	{
		m_firstpos += m_addpos;
		m_firsttar += m_addtar;
		m_cam->SetPos(m_firstpos);
		m_cam->SetTar(m_firsttar);

		if ((m_firstpos - m_lastpos).Length() < 0.5f)
		{
			m_srwin = NewGO<SpriteRender>(0, "sr");
			m_srwin->Init(L"Assets/sprite/win.dds", 462, 262);
			m_srwin->SetPosition({ -410,160,0 });

			m_srteam = NewGO<SpriteRender>(0, "sr");
			if (m_team == 0)
			{
				m_srteam->Init(L"Assets/sprite/redteamp.dds", 768.0f, 315.75f);
			}
			else
			{
				m_srteam->Init(L"Assets/sprite/blueteamp.dds", 795.75f, 315.75f);
			}
			m_srteam->SetPosition({ -240,-210,0 });

			m_cmove = false;
		}
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
	CVector3 poss[3] = { {0,0,0},{30,0,-10},{-30,0,-10} };
	CVector3 pos = CVector3::Zero();
	for (int i = 0; i < mons.size(); i++)
	{
		//CVector3 add = { 30,0,0 };
		//pos += add * i;
		mons[i]->ReleaseMark();

		mons[i]->end();
		mons[i]->Setpos(poss[i]);
		mons[i]->SetRotation(CQuaternion::Identity());
	}
}

void Win::CameraSet()
{
}
