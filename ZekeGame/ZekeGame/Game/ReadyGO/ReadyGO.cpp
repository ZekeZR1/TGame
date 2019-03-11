#include "stdafx.h"
#include "ReadyGO.h"

ReadyGO::~ReadyGO()
{
	DeleteGO(m_ready);
	DeleteGO(m_GO);
}

bool ReadyGO::Start()
{
	m_ready = NewGO<SpriteRender>(30, "sp");
	m_ready->Init(L"Assets/sprite/Ready2.dds", 980.f*0.8f, 388.414f*0.8f);
	m_rpos = { -630,0,0 };
	m_ready->SetPosition(m_rpos);
	
	m_ready->SetScale({ m_rScale,m_rScale ,m_rScale });
	m_ready->SetMulCol({ 1,1,1,m_rAlpha });
	return true;
}

void ReadyGO::Update()
{
	if (m_rAlpha < 1)
	{
		m_rAlpha *= 1.8f;
	}
	else
	{
		m_rAlpha = 1;
	}
	if (m_rpos.x >= -80 && m_rpos.x <= 0)
	{
		m_rScale += 0.18f/80.f;
		m_rpos.x += 120.f/80.f;
	}
	else
	{
		m_rScale += 0.18f;
		m_rpos.x += 120 * (m_rpos.x > -20 ? 1.5f:1);
	}
	if (m_rpos.x >= 20)
		GO();
	if (m_rpos.x >= 1700)
		isEnd = true;

	m_ready->SetPosition(m_rpos);
	m_ready->SetScale({ m_rScale,m_rScale ,m_rScale });
	m_ready->SetMulCol({ 1,1,1,m_rAlpha });


}

void ReadyGO::GO()
{
	if (isFirstGO)
	{
		m_GO = NewGO<SpriteRender>(30, "sp");
		m_GO->Init(L"Assets/sprite/r_go.dds", 1699.f*0.6f, 801.f*0.6f);

		m_GO->SetScale({ m_gScale,m_gScale ,m_gScale });
		isFirstGO = false;
	}
	if (m_gScale <= 1)
	{
		m_gScale *= 1.4f;
	}
	else
		m_gScale *= 1.005f;
	m_GO->SetScale({ m_gScale,m_gScale ,m_gScale });
}
