#include "stdafx.h"
#include "MonAIPresets.h"

#include "MonAIPresetOpenSuper.h"
#include "MonAIPresetIcons.h"

#include "../../GameCursor.h"

void MonAIPresets::OnDestroy()
{
	for (auto o : m_icons)
	{
		DeleteGO(o);
	}
	
}

bool MonAIPresets::Start()
{
	return true;
}

void MonAIPresets::init(MAPopen * mapopen,GameCursor* cur)
{
	m_mapopen = mapopen;
	m_cursor = cur;

	
	
	Preset** presets;
	presets = m_mapopen->GetPresets();
	CVector3 pos = { -480,150,0 };
	pos = { -480,-600,0 };
	m_pos = pos;
	for (int i = 0; i < 6; i++)
	{
		MonAIPresetIcons* icons = NewGO<MonAIPresetIcons>(0, "icons");
		icons->init(presets[i], pos,cur);
		m_icons[i] = icons;
		pos.x += 170;
	}
	//m_pos = pos;
}

void MonAIPresets::Open()
{
	m_State = enOpening;
}

void MonAIPresets::Close()
{
	m_State = enClosing;
}

void MonAIPresets::Update()
{
	int i = 999;

	switch (m_State)
	{
	case enOpening:
	{
		m_pos.y += 125;
		CVector3 pos = m_pos;
		for (int i = 0; i < 6; i++)
		{
			m_icons[i]->Setpos(pos);
			pos.x += 170;
		}
		if (m_pos.y >= 150)
			m_State = enOpen;
	}
		break;
	case enOpen:
		Rotation();
		for (i = 0; i < 6; i++)
		{
			if (m_icons[i]->IsClick())
			{
				break;
			}
			else if (i == 5)
			{
				i = 999;
			}
		}
		break;
	case enClosing:
	{
		m_rotSt = 0;
		m_pos.y -= 125;
		CVector3 pos = m_pos;
		for (int i = 0; i < 6; i++)
		{
			m_icons[i]->Setpos(pos);
			pos.x += 170;
		}
		if (m_pos.y <= -600)
			m_State = enClose;
	}
		break;
	case enClose:
		break;
	}
	
	
	m_clickNum = i;
}

void MonAIPresets::Rotation()
{
	float rotlist[3] = { 2.f, -2.f,0 };
	switch (m_rotSt)
	{
	case 0:
		if (rotlist[0] > m_rot)
		{
			m_rot += 2.f;
			for (auto pres : m_icons)
			{
				pres->Setrot(m_rot);
			}
		}
		else
			m_rotSt++;
		break;
	case 1:
		if (rotlist[1] < m_rot)
		{
			m_rot -= 2.f;
			for (auto pres : m_icons)
			{
				pres->Setrot(m_rot);
			}
		}
		else
			m_rotSt++;
		break;
	case 2:
		if (rotlist[2] > m_rot)
		{
			m_rot += 2.f;
			for (auto pres : m_icons)
			{
				pres->Setrot(m_rot);
			}
		}
		else
			m_rotSt++;
		break;
	}
}

void MonAIPresets::UpdatePreset(int num)
{
	m_icons[num]->UpdateIcon();
}
