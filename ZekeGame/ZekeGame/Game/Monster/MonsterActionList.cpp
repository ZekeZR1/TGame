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

	DeleteGO(m_mp);
	DeleteGO(m_hp);
	DeleteGO(m_fhp);
	DeleteGO(m_fmp);
}

void MonsterActionList::init(Monster * mon)
{
	m_num = mon->Getnum();
	m_mon = mon;

	m_back = NewGO<SpriteRender>(1, "sp");
	float w = 215.0f;
	float h = 144.0f;
	h = 250.0f;
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


	m_hp = NewGO<SpriteRender>(2, "sp");
	m_hp->Init(L"Assets/sprite/mon_hp.dds", 104, 40);
	m_mp = NewGO<SpriteRender>(2, "sp");
	m_mp->Init(L"Assets/sprite/mon_mp.dds", 104, 40);
	
	m_hp->SetPivot({ 0,0 });
	m_mp->SetPivot({ 0,0 });

	m_fhp = NewGO<FontRender>(5, "font");
	m_fmp = NewGO<FontRender>(5, "font");

	pos.y += 45 * 3.2f;
	m_mp->SetPosition(pos);
	m_vm = {pos.x,pos.y};
	m_vm.x += 100;
	m_vm.y += 35;

	pos.y += 45;
	m_hp->SetPosition(pos);
	m_vh = { pos.x,pos.y };
	m_vh.x += 100;
	m_vh.y += 35;
}

bool MonsterActionList::Start()
{
	
	return true;
}

void MonsterActionList::Update()
{
	std::vector<MonsterAction*> mas = m_mon->Getactions();

	float hp = m_mon->GetHP();
	float mp = m_mon->GetMP();

	wchar_t tx[255];
	swprintf_s(tx, L"%.1f", hp);
	m_fhp->Init(tx, m_vh, 0, CVector4::White, 0.9f, { 0,0 });
	swprintf_s(tx, L"%.1f", mp);
	m_fmp->Init(tx, m_vm, 0, CVector4::White, 0.9f, { 0,0 });

	
	int len = mas.size();
	if (len != m_len)
	{
		CVector3 pos = m_back->GetPosition();
		pos.x += 10;
		pos.y += 10;
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


		pos.y -= 4;
		for (int i = 0; i < len; i++)
		{
			CVector3 p = {pos.x,(float)(pos.y + (45 * i)),0 };
			const wchar_t* ws = L"";
			switch (mas[i]->GetactionID())
			{
			case enChase:
				ws = L"追跡";
				break;
			case enAtack:
				ws = L"パンチ";
				break;
			case enLeave:
				ws = L"逃げる";
				break;
			case enDefense:
				ws = L"守る";
				break;
			case enFire:
				ws = L"ファイア";
				break;
			case enTackle:
				ws = L"タックル";
				break;
			case enGuardian:
				ws = L"守護";
				break;
			case enRecovery:
				ws = L"回復";
			}
			m_frs[i]->Init(ws, { p.x,p.y +45}, 0, CVector4::White, 1, { 0,0 });
		}

		m_len = len;
	}
}

void MonsterActionList::PostRender()
{
}
