#include "stdafx.h"
#include "MonAIPresetIcon.h"

#include "../../GameData.h"

void MonAIPresetIcon::OnDestroy()
{
	DeleteGO(m_Icon);
	DeleteGO(m_font);
}

MonAIPresetIcon::~MonAIPresetIcon()
{
	
}

bool MonAIPresetIcon::Start()
{
	return true;
}

void MonAIPresetIcon::init(int monID, const wchar_t* pypath,CVector3 pos)
{
	m_Icon = NewGO<SpriteRender>(20, "sp");
	m_Icon->Init(GameData::GetMonsterIconPath(monID), 150, 170);
	m_Icon->SetPosition(pos);

	pos.x -= 80;
	pos.y -= 30;
	m_font = NewGO<FontRender>(21, "fr");
	m_font->Init(pypath, pos.ToTwo(), 0, CVector4::White, 1, {0,0});
	m_font->DrawShadow();
}

void MonAIPresetIcon::Update()
{
}
