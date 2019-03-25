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

	
	
	Preset* presets;
	presets = m_mapopen->GetPresets();
	CVector3 pos = { -480,150,0 };
	for (int i = 0; i < 6; i++)
	{
		MonAIPresetIcons* icons = NewGO<MonAIPresetIcons>(0, "icons");
		icons->init(presets[i], pos,cur);
		m_icons[i] = icons;
		pos.x += 170;
	}
}

void MonAIPresets::Update()
{
	int i = 999;
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
	m_clickNum = i;
}
