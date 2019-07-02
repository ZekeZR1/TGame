#include "stdafx.h"
#include "Win.h"
#include "../ResultCamera.h"
#include "../../NetPVP/NetAISelect.h"
#include "../../Game.h"
#include "../../Title/pvpModeSelect.h"
#include "../../Monster/Monster.h"
#include "../../GameData.h"

#include "../../Fade/Fade.h"
#include "../../Fade/MusicFade.h"

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
	if (m_mode == Game::enRandomPVP) {
		NewGO<NetAISelect>(0, "pvp");
	}
	else if (m_mode == Game::enLocalPVP) {
		NewGO<PvPModeSelect>(0, "pvp");
	}
	DeleteGO(m_sr);
	DeleteGO(m_cam);
	DeleteGO(m_srteam);
	DeleteGO(m_srwin);
	DeleteGO(FindGO<Game>("Game"));

	DeleteGO(m_nextfont);
	
}

void Win::OnDestroy()
{
	m_BGM->Stop();
}

void Win::init(int team, Game::Mode mode)
{
	m_cam = NewGO<ResultCamera>(0, "rescam");
	m_mode = mode;
	m_firstpos = { -350,10,500 };
	m_firsttar = { 0,30,0 };

	m_cam->SetPos(m_firstpos);
	m_cam->SetTar(m_firsttar);

	//m_lastpos = { -35,50,50 };
	//m_lasttar = { 0,55,0 };

	float hie = g_mons[0]->Getheight();
	m_lastpos = { hie/-13+hie/-5, hie/2+hie/7.3f, hie/10 + hie /4 };
	m_lasttar = { 15, hie/2+hie/7.f, 0 };

	/*switch (g_mons[0]->GetID())
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
	}*/

	m_addpos = (m_lastpos - m_firstpos) / 10.0f;
	m_addtar = (m_lasttar - m_firsttar) / 10.0f;

	m_team = team;
	MonsterSet();
	CameraSet();
}

bool Win::Start()
{
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	return true;
}

void Win::Update()
{
	

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
			if (m_mode == Game::enRandomPVP) {
				m_BGM->Init(L"Assets/sound/BGM/PerituneMaterial_OverWorld5_loop.wav", true);
			}
			else if (m_mode == Game::enLocalPVP) {
				if (m_team == 0) {
					m_BGM->Init(L"Assets/sound/BGM/PerituneMaterial_OverWorld5_loop.wav", true);
				}
				else {
					m_BGM->Init(L"Assets/sound/losebgm.wav", true);
				}
			}
			m_BGM->Play();

			m_nextfont = NewGO<FontRender>(5, "fr");
			m_nextfont->SetTextType(CFont::en_Japanese);
			m_nextfont->Init(L"ƒNƒŠƒbƒN‚µ‚Ä‚­‚¾‚³‚¢", { -600,-300 }, 0, { 1,1,1,1 }, 1, { 0,0 });
			m_nextfont->DrawShadow();

			m_cmove = false;
		}
	}
	else
	{
		
		if (Mouse::isTrigger(enLeftClick))
		{
			m_fade->FadeOut();
			m_isClick = true;
			MusicFade* mf = NewGO<MusicFade>(0, "mf");
			mf->init(m_BGM, 0.15f);
		}
		if (m_fade->isFadeStop() && m_isClick)
		{
			DeleteGO(this);
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
		mons[i]->anim_idle();
	}
}

void Win::CameraSet()
{
}
