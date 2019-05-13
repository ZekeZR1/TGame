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

void Win::OnDestroy()
{
	m_BGM->Stop();
}

void Win::init(int team)
{
	m_cam = NewGO<ResultCamera>(0, "rescam");

	m_firstpos = { -350,10,500 };
	m_firsttar = { 0,30,0 };

	m_cam->SetPos(m_firstpos);
	m_cam->SetTar(m_firsttar);

	m_lastpos = { -35,50,50 };
	m_lasttar = { 0,55,0 };
	switch (g_mons[0]->GetID())
	{
	case enTest:
		break;
	case enUmataur:
		m_lastpos = { -20,150,72 };
		m_lasttar = { 30,165,0 };
		break;
	case enFairy:
		m_lastpos = { -35,90,50 };
		m_lasttar = { 0,90,0 };
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
			//m_srwin->Init(L"Assets/sprite/win.dds", 462, 262);
			m_srwin->Init(L"Assets/sprite/res_Win.dds", 462*1.1f, 183.256f*1.1f);
			m_srwin->SetPivot({ 0,0.5f });
			m_srwin->SetPosition({ -610,210,0 });

			m_srteam = NewGO<SpriteRender>(0, "sr");
			if (m_team == 0)
			{
				//m_srteam->Init(L"Assets/sprite/redteamp.dds", 768.0f, 315.75f);
				m_srteam->Init(L"Assets/sprite/res_redteam.dds", 768.0f*1.5f, 212.21f*1.5f);
			}
			else
			{
				//m_srteam->Init(L"Assets/sprite/blueteamp.dds", 795.75f, 315.75f);
				m_srteam->Init(L"Assets/sprite/res_blueteam.dds", 795.75f*1.5f, 212.21f*1.5f);
			}
			m_srteam->SetPivot({ 0,0.5f });
			m_srteam->SetPosition({ -620,-210,0 });

			m_BGM = NewGO<Sound>(0, "BGM");
			m_BGM->Init(L"Assets/sound/BGM/PerituneMaterial_OverWorld5_loop.wav", true);
			m_BGM->Play();

			m_cmove = false;
		}
	}
	else
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
		mons[i]->anim_idle();
	}
}

void Win::CameraSet()
{
}
