#include "stdafx.h"
#include "GameLog.h"

GameLog* GameLog::instans = nullptr;

GameLog::GameLog()
{
	m_logs = new Log[m_logMax];

	CVector2 pos = { -630,350 };
	for (int i = 0; i < m_logMax; i++)
	{
		m_logs[i].font = NewGO<FontRender>(0, "fr");
		m_logs[i].font->SetTextType(CFont::en_JPLog);
		m_logs[i].font->Init(L"", pos, 0, { 1,1,1,1 }, 0.5f);
		pos.y -= 25;
	}
}

void GameLog::OnDestroy()
{
	int i = m_logMax;
	while (i)
	{
		DeleteGO(m_logs[--i].font);
	}
	delete[] m_logs;
}

#define LOGSTATE  m_logs[i].font->GetPosition(), 0, { 1,1,1,1 }, 0.5f

void GameLog::Update()
{
	float dt = IGameTime().GetFrameDeltaTime();
	for (int i = 0; i < m_logMax; i++)
	{
		if (m_logs[i].isDead)
			continue;

		m_logs[i].timeLim -= dt;

		if (m_logs[i].timeLim <= 0.f)
		{
			m_logs[i].isDead = true;
			m_logs[i].font->Init(L"", LOGSTATE);
		}
	}
}

void GameLog::MMprint(std::wstring str)
{
	for (int i = m_logMax-1; i >= 0; i--)
	{
		if (m_logs[i].isDead)
			continue;
		if (i == m_logMax - 1)
		{
			m_logs[i].font->Init(L"", LOGSTATE);
			m_logs[i].isDead = true;
			m_logs[i].timeLim = m_timeMax;
		}
		else
		{
			m_logs[i + 1].font->Init(m_logs[i].font->getText(), m_logs[i+1].font->GetPosition(), 0, { 1,1,1,1 }, 0.5f);
			m_logs[i + 1].isDead = m_logs[i].isDead;
			m_logs[i + 1].timeLim = m_logs[i].timeLim;
		}
	}
	int i = 0;
	m_logs[0].font->Init(str.c_str(), LOGSTATE);
	m_logs[0].isDead = false;
	m_logs[0].timeLim = m_timeMax;
}
