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
	//m_arrow->Init(L"Assets/sprite/returnArrow.dds", m_buttonSize.x, m_buttonSize.y);
	m_arrow->Init(L"Assets/sprite/Rarrow0.dds", m_buttonSize.x, m_buttonSize.y);
	m_arrow->SetPivot({ 0,0 });
	m_arrow->SetPosition({ -640,-360,0 });

	m_arrowpos = { -508,-275.5f,0 };

	

	m_bow = NewGO<SpriteRender>(2, "sp");
	m_bow->Init(L"Assets/sprite/Rarrow2.dds", m_bowsize.x * m_scale, m_bowsize.y * m_scale);
	m_bow->SetScale({ m_bowsca,1,1 });
	m_bow->SetPosition(m_arrowpos);
	m_bow->SetPivot({ 1,0.5 });

	m_top = NewGO<SpriteRender>(2, "sp");

	m_top->Init(L"Assets/sprite/Rarrow1.dds", m_topsize.x * m_scale, m_topsize.y * m_scale);
	CVector3 bowpos = m_arrowpos;
	bowpos.x -= m_bowsca * 80;
	m_top->SetPosition(bowpos);
}

void ReturnButton::SetScene(GameObject* scene)
{
	m_scene = scene;
}

void ReturnButton::OnDestroy()
{
	DeleteGO(m_button);
	DeleteGO(m_arrow);

	DeleteGO(m_top);
	DeleteGO(m_bow);
}


