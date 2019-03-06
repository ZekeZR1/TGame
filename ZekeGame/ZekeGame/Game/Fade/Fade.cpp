  //////////////////////
 //My name in "fade".//
//////////////////////

#include "stdafx.h"
#include "Fade.h"

Fade::Fade()
{
	m_black = NewGO<SpriteRender>(31, "sp");
	m_black->Init(L"Assets/sprite/fade_black.dds", 1280,720);
	m_black->SetMulCol(m_mulcol);
}

void Fade::OnDestroy()
{
	DeleteGO(m_black);
}

void Fade::Update()
{
	switch (m_state)
	{
	case enFadein:
	{
		float add = m_speed * IGameTime().GetFrameDeltaTime();
		m_mulcol.w -= add;
		if (m_mulcol.w <= 0)
		{
			m_mulcol.w = 0;
			m_state = enFadeStop;
		}
		m_black->SetMulCol(m_mulcol);
	}
		break;
	case enFadeout:
	{
		float add = m_speed * IGameTime().GetFrameDeltaTime();
		m_mulcol.w += add;
		if (m_mulcol.w >= 1)
		{
			m_mulcol.w = 1;
			m_state = enFadeStop;
		}
		m_black->SetMulCol(m_mulcol);
		break;
	}
	}
}
