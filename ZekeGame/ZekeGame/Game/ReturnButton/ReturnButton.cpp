#include "stdafx.h"
#include "ReturnButton.h"

#include "../GameCursor.h"

ReturnButton::ReturnButton()
{
	m_fade = FindGO<Fade>("fade");

	m_button = NewGO<SpriteRender>(2, "sp");

	m_buttonSize.x /= 2;
	m_buttonSize.y /= 2;
	m_button->Init(L"Assets/sprite/returnButton.dds", m_buttonSize.x, m_buttonSize.y,true);
	m_button->SetPivot({ 0,0 });
	m_button->SetPosition({ -640,-360,0 });

	m_arrow = NewGO<SpriteRender>(2,"sp");
	m_arrow->Init(L"Assets/sprite/returnArrow.dds", m_buttonSize.x, m_buttonSize.y);
	m_arrow->SetPivot({ 0,0 });
	m_arrow->SetPosition({ -640,-360,0 });
}

void ReturnButton::SetScene(GameObject* scene)
{
	m_scene = scene;
}

void ReturnButton::OnDestroy()
{
	DeleteGO(m_button);
	DeleteGO(m_arrow);
}


