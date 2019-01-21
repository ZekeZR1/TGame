#include "stdafx.h"
#include "MonsterActionList.h"

#include "../GameData.h"
#include "Monster.h"
#include "MonsterAction.h"

MonsterActionList::~MonsterActionList()
{
	DeleteGO(m_back);
	DeleteGO(m_icon);
	for (auto a : m_actBlocks)
		DeleteGO(a);
	for (auto a : m_frs)
		DeleteGO(a);
}

void MonsterActionList::init(Monster * mon)
{
	m_num = mon->Getnum();
	m_mon = mon;

	m_back = NewGO<SpriteRender>(1, "sp");
	float w = 215.0f;
	float h = 144.0f;
	if (mon->Getteam() == 0)
	{
		m_back->Init(L"Assets/Sprite/backRed.dds", w, h);
	}
	else
	{
		m_back->Init(L"Assets/Sprite/backBlue.dds", w, h);
	}
	m_back->SetPivot({ 0,0 });
	m_back->SetPosition({ (float)(m_num * (w-5))-630.0f,-360,0 });
	//m_icon = NewGO<SpriteRender>(9, "sp");

	
	CVector3 pos = m_back->GetPosition();
	for (int i = 0; i < 3; i++)
	{
		FontRender* fr = NewGO<FontRender>(5, "font");
		m_frs[i] = fr;
	}
}

bool MonsterActionList::Start()
{
	
	return true;
}

void MonsterActionList::Update()
{
	std::vector<MonsterAction*> mas = m_mon->Getactions();
	
	int len = mas.size();
	if (len != m_len)
	{
		CVector3 pos = m_back->GetPosition();
		if (len < m_len)
		{
			for (int i = m_len-1; i > len-1; i--)
			{
				DeleteGO(m_actBlocks[i]);
				m_actBlocks.erase(std::find(m_actBlocks.begin(),m_actBlocks.end(), m_actBlocks[i]));
			}
		}
		else
		{
			for (int i = m_len; i < len; i++)
			{
				SpriteRender* sp = NewGO<SpriteRender>(2, "sp");
				sp->Init(L"Assets/sprite/actBlock.dds", 150, 40);
				sp->SetPivot({ 0,0 });
				CVector3 p = { pos.x,(float)(pos.y + (45 * i)),0 };
				sp->SetPosition(p);
				m_actBlocks.push_back(sp);
			}
		}
		for (auto a : m_frs)
			a->Init(L"", { 0,0 }, 0, CVector4::White, 1, { 0,0 });


		
		for (int i = 0; i < len; i++)
		{
			CVector3 p = {pos.x,(float)(pos.y + (45 * i)),0 };
			const wchar_t* ws = L"";
			switch (mas[i]->GetactionID())
			{
			case enChase:
				ws = L"Chase";
				break;
			case enAtack:
				ws = L"Atack";
				break;
			case enLeave:
				ws = L"Leave";
				break;
			}
			m_frs[i]->Init(ws, { p.x,p.y +45}, 0, CVector4::White, 1, { 0,0 });
		}

		m_len = len;
	}
}

void MonsterActionList::PostRender()
{
}
