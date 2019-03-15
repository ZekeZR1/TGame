#include "stdafx.h"
#include "MonAIPresetOpen.h"
#include "../SuperMonsterSelect.h"
#include "../../GameCursor.h"

#include "MonAIPreset.h"

bool MonAIPresetOpen::Start()
{
	CVector3 pos = { -540,250,0 };
	m_button = NewGO<SpriteRender>(2, "sp");
	m_button->Init(L"Assets/sprite/fade.dds", 70, 40);
	m_button->SetPosition(pos);
	m_button->SetMulCol({ 0.5,0.5,0.5,1 });

	m_dummy = NewGO<SpriteRender>(2, "sp");
	m_dummy->Init(L"", 70, 40, true);
	m_dummy->SetPosition(pos);

	m_font = NewGO<FontRender>(3, "fr");
	m_font->SetTextType(CFont::en_Japanese);
	m_font->Init(L"プリセット", { pos.x,pos.y }, 0, CVector4::White, 1, { 0,0 });

	return true;
}

void MonAIPresetOpen::init(SuperMonsterSelect * sms, GameCursor * cursor, int team)
{
	m_sms = sms;
	m_cursor = cursor;
	m_team = team;
}

void MonAIPresetOpen::Update()
{
	m_isClick = false;
	m_dummy->SetCollisionTarget(m_cursor->GetCursor());

	if (m_dummy->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;
		}
	}
}

void MonAIPresetOpen::OpenPreset()
{
	MonAIPreset* map = NewGO<MonAIPreset>(0, "amp");
	map->init(m_sms, m_cursor, this, m_team);

	m_isOpen = true;
}
