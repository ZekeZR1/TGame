#include "stdafx.h"
#include "IconAI.h"
#include "../GameCursor.h"

#include <string>

IconAI::~IconAI()
{
	DeleteGO(m_frame);
	DeleteGO(m_dummy);
	DeleteGO(m_fr);
}

bool IconAI::Start()
{
	
	return true;
}

void IconAI::init(std::string py,int num,GameCursor* cursor)
{
	m_cursor = cursor;
	std::wstring ws = std::wstring(py.begin(), py.end());
	m_py = ws;
	m_num = num;
	m_frame = NewGO<SpriteRender>(6, "sp");
	if (((m_num + 1) % 2) == 0)
		m_frame->Init(L"Assets/sprite/ai_even.dds", 372, 77);
	else
		m_frame->Init(L"Assets/sprite/ai_odd.dds", 372, 77);
	m_dummy = NewGO<SpriteRender>(0, "sp");
	m_dummy->Init(nullptr, 372, 77, true);

	m_fr = NewGO<FontRender>(25, "font");
	//m_fr->Init(m_py, { pos.x - 150 ,pos.y + 20 }, 0, CVector4::White, 1, { 0.5f,0.5f });
}

void IconAI::Update()
{
	m_isClick = false;
	m_dummy->SetCollisionTarget(m_cursor->GetCursor());
	if (m_dummy->isCollidingTarget())
	{
		if (!m_issel)
		{
			m_frame->Init(L"Assets/sprite/ai_sel.dds", 372, 77);
			m_issel = true;
		}
		if (Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;
		}
	}
	else
	{
		if (m_issel)
		{
			if (((m_num + 1) % 2) == 0)
				m_frame->Init(L"Assets/sprite/ai_even.dds", 372, 77);
			else
				m_frame->Init(L"Assets/sprite/ai_odd.dds", 372, 77);
			m_issel = false;
		}
	}
}

void IconAI::PostRender()
{
	//CVector3 pos = m_frame->GetPosition();
	//m_fr->Init(m_py, {pos.x-150 ,pos.y+20 }, 0, CVector4::White, 1, { 0.5f,0.5f });
}

void IconAI::Setpos(CVector3 pos)
{
	m_frame->SetPosition(pos);
	m_dummy->SetPosition(pos);
	m_fr->Init(m_py.c_str(), { pos.x - 150 ,pos.y + 20 }, 0, CVector4::White, 1, { 0.5f,0.5f });
}

CVector3 IconAI::Getpos()
{
	return m_frame->GetPosition();
}
