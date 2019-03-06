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
	DeleteGO(m_monNumBack);
	DeleteGO(m_monNum);
	DeleteGO(m_SmonNum);

	DeleteGO(m_HPfr);
	DeleteGO(m_MPfr);

	DeleteGO(m_SHPfr);
	DeleteGO(m_SMPfr);
	DeleteGO(m_Sfhp);
	DeleteGO(m_Sfmp);
	for (auto a : m_Sfrs)
		DeleteGO(a);
}

void MonsterActionList::init(Monster * mon)
{
	m_num = mon->Getnum();
	m_mon = mon;

	m_back = NewGO<SpriteRender>(1, "sp");
	float w = 215.0f;
	float h = 144.0f;
	h = 215.0f;
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

	/*m_monNum = NewGO<SpriteRender>(1, "sp");
	if (mon->Getteam() == 0)
	{
		switch (mon->Getnum())
		{
		case 0:
			m_monNum->Init(L"Assets/Sprite/mon_actlist_Red1.dds", w, h);
			break;
		case 1:
			m_monNum->Init(L"Assets/Sprite/mon_actlist_Red2.dds", w, h);
			break;
		case 2:
			m_monNum->Init(L"Assets/Sprite/mon_actlist_Red3.dds", w, h);
			break;
		}
		
	}
	else
	{
		int num = mon->Getnum()-3;
		switch (num)
		{
		case 0:
			m_monNum->Init(L"Assets/Sprite/mon_actlist_Red1.dds", w, h);
			break;
		case 1:
			m_monNum->Init(L"Assets/Sprite/mon_actlist_Red2.dds", w, h);
			break;
		case 2:
			m_monNum->Init(L"Assets/Sprite/mon_actlist_Red3.dds", w, h);
			break;
		}
	}*/
	//m_monNum->SetPivot({ 0,0 });
	//m_monNum->SetPosition({ (float)(m_num * (w - 5)) - 630.0f,-360,0 });

	CVector3 pos = m_back->GetPosition();
	for (int i = 0; i < 3; i++)
	{
		FontRender* fr = NewGO<FontRender>(4, "fr");
		m_Sfrs[i] = fr;

		fr = NewGO<FontRender>(5, "font");
		m_frs[i] = fr;
		
	}


	//m_hp = NewGO<SpriteRender>(2, "sp");
	//m_hp->Init(L"Assets/sprite/mon_hp.dds", 104, 40);
	//m_mp = NewGO<SpriteRender>(2, "sp");
	//m_mp->Init(L"Assets/sprite/mon_mp.dds", 104, 40);
	
	//m_hp->SetPivot({ 0,0 });
	//m_mp->SetPivot({ 0,0 });

	m_fhp = NewGO<FontRender>(5, "font");
	m_fmp = NewGO<FontRender>(5, "font");

	pos.y += 45 * 3.2f;
	//m_mp->SetPosition(pos);

	

	

	m_vm = {pos.x,pos.y};
	m_vm.y += 28;

	m_SMPfr = NewGO<FontRender>(2, "fr");
	m_SMPfr->Init(L"MP:", { m_vm.x+10 + 5 ,m_vm.y - 5 }, 0, { 0,0,0,1 }, 0.6f, { 0,0 });

	m_MPfr = NewGO<FontRender>(2, "fr");
	m_MPfr->Init(L"MP:", { m_vm.x+10,m_vm.y}, 0, CVector4::White, 0.6f, { 0,0 });

	m_vm.x += 100;
	

	pos.y += 45;
	//m_hp->SetPosition(pos);
	

	m_vh = { pos.x,pos.y };
	m_vh.y += 14;

	m_SHPfr = NewGO<FontRender>(2, "fr");
	m_SHPfr->Init(L"HP:", { m_vh.x+10+5,m_vh.y-5}, 0, { 0,0,0,1 }, 0.6f, { 0,0 });

	m_HPfr = NewGO<FontRender>(2, "fr");
	m_HPfr->Init(L"HP:", { m_vh.x+10,m_vh.y }, 0, CVector4::White, 0.6f, { 0,0 });


	m_monNumBack = NewGO<SpriteRender>(2, "sp");
	int team = mon->Getteam();
	if (team == 1)
		m_monNumBack->Init(L"Assets/sprite/mark_blue.dds", 50* 0.59375f, 50);
	else
		m_monNumBack->Init(L"Assets/sprite/mark_red.dds", 50* 0.59375f, 50);

	m_monNumBack->SetPosition({ m_vh.x+6,m_vh.y-5,0 });
	m_monNumBack->SetPivot({ 0,0 });

	
	wchar_t ws[3];
	swprintf_s(ws,L"%d", mon->Getnum() - (team == 0 ? -1 : 2));

	m_SmonNum = NewGO<FontRender>(2,"fr");
	m_SmonNum->Init(ws, { m_vh.x +6+ 3 + 2,m_vh.y - 9 + 50 - 2 }, 0, { 0,0,0,1 }, 0.5f, { 0,0 });

	m_monNum = NewGO<FontRender>(2, "fr");
	m_monNum->Init(ws, { m_vh.x+6+3,m_vh.y - 9 + 50 }, 0, CVector4::White, 0.5f, { 0,0 });

	

	m_vh.x += 100;
	

	

	m_Sfhp = NewGO<FontRender>(4, "fr");
	m_Sfmp = NewGO<FontRender>(4, "fr");
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
	m_fhp->Init(tx, m_vh, 0, CVector4::White, 0.6f, { 0,0 });

	m_Sfhp->Init(tx, { m_vh.x + 5,m_vh.y - 5 }, 0, { 0,0,0,1 }, 0.6f, { 0,0 });

	swprintf_s(tx, L"%.1f", mp);
	m_fmp->Init(tx, m_vm, 0, CVector4::White, 0.6f, { 0,0 });
	m_Sfmp->Init(tx, { m_vm.x + 5,m_vm.y - 5 }, 0, { 0,0,0,1 }, 0.6f, { 0,0 });
	
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
				sp->Init(L"Assets/sprite/actBlock.dds", 195, 40);
				sp->SetPivot({ 0,0 });
				CVector3 p = { pos.x,(float)(pos.y + (45 * i)),0 };
				sp->SetPosition(p);
				m_actBlocks.push_back(sp);
			}
		}
		for (auto a : m_frs)
			a->Init(L"", { 0,0 }, 0, CVector4::White, 1, { 0,0 });
		for (auto a : m_Sfrs)
			a->Init(L"", { 0,0 }, 0, CVector4::White, 1, { 0,0 });

		pos.y -= 4;
		for (int i = 0; i < len; i++)
		{
			CVector3 p = {pos.x,(float)(pos.y + (45 * i)),0 };
			const wchar_t* ws = L"";
			switch (mas[i]->GetactionID())
			{
			case enChase:
				//ws = L"追跡";
				ws = L"CHASE";
				break;
			case enAtack:
				//ws = L"パンチ";
				ws = L"ATTACK";
				break;
			case enLeave:
				//ws = L"逃げる";
				ws = L"ESCAPE";
				break;
			case enDefense:
				//ws = L"守る";
				ws = L"DEFENSE";
				break;
			case enFire:
				//ws = L"ファイア";
				ws = L"FIRE";
				break;
			case enTackle:
				//ws = L"タックル";
				ws = L"TACKLE";
				break;
			case enGuardian:
				//ws = L"守護";
				ws = L"GUARDIAN";
				break;
			case enRecovery:
				//ws = L"回復";
				ws = L"HEAL";
			}
			m_frs[i]->Init(ws, { p.x,p.y +45-5}, 0, CVector4::White, 0.7f, { 0,0 });
			m_Sfrs[i]->Init(ws, { p.x+5,p.y + 45-5-5 }, 0, {0,0,0,1}, 0.7f, { 0,0 });
		}

		m_len = len;
	}
}

void MonsterActionList::PostRender()
{
}
