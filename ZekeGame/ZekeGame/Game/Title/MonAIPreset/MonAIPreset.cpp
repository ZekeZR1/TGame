#include "stdafx.h"
#include "MonAIPreset.h"

#include "MonAIPresetLoad.h"
#include "MonAIPresetSave.h"

#include "../SuperMonsterSelect.h"
#include "../../GameCursor.h"

MonAIPreset::~MonAIPreset()
{
	for (auto o : m_maps)
	{
		DeleteGO(o);
	}
	for (auto o : m_mapl)
	{
		DeleteGO(o);
	}
}

bool MonAIPreset::Start()
{
	CVector3 pos = { -540,-170,0 };

	for (int i = 0; i < 6; i++)
	{
		MonAIPresetSave* maps = NewGO<MonAIPresetSave>(0, "maps");
		maps->init(m_sms,i,m_cursor);
		maps->setPos(pos);

		pos.y -= 80;

		MonAIPresetLoad* mapl = NewGO<MonAIPresetLoad>(0, "mapl");
		mapl->init(m_sms, i, m_team, m_cursor);
		mapl->setPos(pos);

		pos.y += 80;
		pos.x += 130;
	}
	return true;
}

void MonAIPreset::init(SuperMonsterSelect * sms, GameCursor * cursor, MonAIPresetOpen * mapo, int team)
{
	m_sms = sms;
	m_cursor = cursor;
	m_mapo = mapo;
	m_team = team;
}

void MonAIPreset::Update()
{
}

void MonAIPreset::Close()
{
}
