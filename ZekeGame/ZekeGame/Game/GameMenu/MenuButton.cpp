#include "stdafx.h"
#include "MenuButton.h"

#include "../GameCursor.h"

MenuButton::~MenuButton()
{
	DeleteGO(m_button);
	DeleteGO(m_moji);
	DeleteGO(m_dummy);
}

bool MenuButton::Start()
{
	m_button = NewGO<SpriteRender>(28, "sp");
	m_button->Init(L"Assets/sprite/simple_button.dds", 400.0f, 89.6f);
	m_dummy = NewGO<SpriteRender>(0, "sp");
	m_dummy->Init(L"", 400.0f, 89.6f, true);

	m_button->SetPosition(m_pos);
	m_dummy->SetPosition(m_pos);
	if (m_moji != nullptr)
		m_moji->SetPosition(m_pos);
	return true;
}

void MenuButton::Update()
{
	m_isClick = false;
	m_dummy->SetCollisionTarget(m_cursor->GetCursor());
	if (m_dummy->isCollidingTarget())
	{
		if (!m_isSelect)
		{
			m_button->Init(L"Assets/sprite/simple_button_blue.dds", 400.0f, 89.6f);
			m_isSelect = true;
		}
		if (g_pad[0].IsTrigger(enButtonA) || Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;
		}
	}
	else
	{
		if (m_isSelect)
		{
			m_button->Init(L"Assets/sprite/simple_button.dds", 400.0f, 89.6f);
			m_isSelect = false;
		}
	}
}
