#include "stdafx.h"
#include "MonAIPreset.h"

#include "MonAIPresetLoad.h"
#include "MonAIPresetSave.h"
#include "MonAIPresetOpen.h"

#include "../SuperMonsterSelect.h"
#include "../../GameCursor.h"

MonAIPreset::~MonAIPreset()
{
	
}

void MonAIPreset::OnDestroy()
{
	for (auto o : m_maps)
	{
		DeleteGO(o);
	}
	for (auto o : m_mapl)
	{
		DeleteGO(o);
	}
	DeleteGO(m_return);
	DeleteGO(m_rDummy);
	m_mapo->Close();
}

bool MonAIPreset::Start()
{
	CVector3 pos = { -500,-170,0 };

	for (int i = 0; i < 6; i++)
	{
		MonAIPresetSave* maps = NewGO<MonAIPresetSave>(0, "maps");
		maps->init(m_sms,i,m_cursor);
		maps->setPos(pos);
		m_maps[i] = maps;
		pos.y -= 80;

		MonAIPresetLoad* mapl = NewGO<MonAIPresetLoad>(0, "mapl");
		mapl->init(m_sms, i, m_team, m_cursor,this);
		mapl->setPos(pos);
		m_mapl[i] = mapl;

		pos.y += 80;
		pos.x += 170;
	}

	pos = { 550,-310,0 };

	m_return = NewGO<SpriteRender>(6, "sp");
	m_return->Init(L"Assets/sprite/fade_black.dds", 80, 50);
	m_return->SetPosition(pos);

	m_rDummy = NewGO<SpriteRender>(0, "sp");
	m_rDummy->Init(L"", 80, 50, true);
	m_rDummy->SetPosition(pos);

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
	m_rDummy->SetCollisionTarget(m_cursor->GetCursor());
	if (m_rDummy->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			Close();
		}
	}
}

void MonAIPreset::Close()
{
	
	DeleteGO(this);
}
