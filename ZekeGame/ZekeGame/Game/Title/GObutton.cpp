#include "stdafx.h"
#include "GObutton.h"

#include "../GameCursor.h"

GObutton::GObutton()
{
}

void GObutton::init(GameCursor* cursor, CVector3 pos)
{
	m_cursor = cursor;

	m_button = NewGO<SpriteRender>(0, "sp");
	m_button->Init(L"Assets/sprite/GO.dds", 193, 93, true);
	m_button->SetPosition(pos);

}

void GObutton::OnDestroy()
{
	DeleteGO(m_button);
}

void GObutton::Update()
{
	
}

void GObutton::UpdateEx()
{
	m_isClick = false;

	m_button->SetCollisionTarget(m_cursor->GetCursor());

	if (m_button->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;
		}
		if (!m_isOver)
		{
			m_button->SetScale({ 1.1f,1.1f ,1 });
			m_isOver = true;
		}
	}
	else if (m_isOver)
	{
		m_button->SetScale({ 1.f,1.f ,1 });
		m_isOver = false;
	}
}
