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
		m_pos.y += 60;
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
		m_pos.y -= 60;
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

void MonAIPresets::UpdatePreset(int num)
{
	m_icons[num]->UpdateIcon();
}
