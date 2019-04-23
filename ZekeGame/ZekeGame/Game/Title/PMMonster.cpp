#include "stdafx.h"
#include "PMMonster.h"
#include "AIMSelect.h"
#include "../GameData.h"
#include "../GameCursor.h"
#include "MonsterSelect.h"
#include "AISelect.h"

PMMonster::~PMMonster()
{
	DeleteGO(m_frame);
	DeleteGO(m_mon);
	DeleteGO(m_fr);
	DeleteGO(m_frShadow);
}

PMMonster::PMMonster()
{
	m_mon = NewGO<SpriteRender>(1, "sp");
	//m_mon->Init(L"Assets/sprite/mon_one.dds", 240, 340,true);
	m_frShadow = NewGO<FontRender>(1, "font");
	m_fr = NewGO<FontRender>(1, "font");
	m_cursor = FindGO<GameCursor>("cursor");
}

bool PMMonster::Start()
{
	
	
	return true;
}

void PMMonster::init(int num,CVector3 pos)
{
	m_num = num;
	int t = m_num+1-3;
	if (t <= 0)
		m_team = 0;
	else
		m_team = 1;

	m_frame = NewGO<SpriteRender>(0, "sp");
	if (m_team == 0)
		m_frame->Init(L"Assets/sprite/mon_frameRed.dds", 240, 340);
	else
		m_frame->Init(L"Assets/sprite/mon_frameBlue.dds", 240, 340);
	
	m_frame->SetPosition(pos);

	ChengeImage(g_monset[m_num]);
	m_mon->SetPosition(pos);
}

void PMMonster::Update()
{
	
}

void PMMonster::UpdateEX()
{
	m_isClick = false;
	if (m_ismonsel && Mouse::isTrigger(enRightClick))
	{
		DeleteGO(m_ms);
		DeleteGO(m_ais);
		m_ismonsel = false;
	}

	/*CVector3 v = m_cursor->GetCursor();
	v -= m_mickey;
	if (v.Length() < 0.1f)
	{
		return;
	}*/

	bool isothersel = false;
	bool issel = false;
	QueryGOs<PMMonster>("pmm", [&](PMMonster* pmm)->bool
	{
		if (pmm->isMonSel())
		{
			isothersel = true;
			return false;
		}
		if (!issel && pmm->isSelect() && pmm != this)
		{
			issel = true;
		}
		return true;
	});
	if (isothersel)
		return;
	m_mon->SetCollisionTarget(m_cursor->GetCursor());

	if (!m_ismonsel && m_mon->isCollidingTarget())
	{
		if (!m_issel)
		{
			m_frame->Init(L"Assets/sprite/mon_frameYellow.dds", 240, 340);
			m_issel = true;
		}
		if (Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;
			AIMSelect* aims = NewGO<AIMSelect>(0, "aims");
			aims->init(this, m_selAI, m_monid);
			m_ismonsel = true;
			m_isOpen = true;
		}
	}
	else
	{
		if (m_issel /*&& issel*/)
		{
			if (m_team == 0)
				m_frame->Init(L"Assets/sprite/mon_frameRed.dds", 240, 340);
			else
				m_frame->Init(L"Assets/sprite/mon_frameblue.dds", 240, 340);
			m_issel = false;
		}
	}
}

void PMMonster::Open()
{
	
}

void PMMonster::ChengeImage(int monid)
{
	/*wchar_t ws[255] ;
	GameData::GetMonsterIconPath(ws, monid);
	m_mon->Init(ws, 128, 128);
	m_monid = (MonsterID)monid;
	delete[] ws;*/
	m_monid = (MonsterID)monid;
	m_mon->Init(GameData::GetMonsterIconPath(monid), 240, 340,true);
	/*switch (monid)
	{
	case enTest:
		m_mon->Init(L"Assets/sprite/mon_one.dds", 128, 128);
		break;
	case enUmataur:
		m_mon->Init(L"Assets/sprite/mon_two.dds", 128, 128);
		break;
	case enFairy:
		m_mon->Init(L"Assets/sprite/mon_three.dds", 128, 128);
		break;
	}*/

	g_monset[m_num] = monid;
	//m_path = path;
}

void PMMonster::SetPython(const wchar_t * py,int num, int AImode)
{
	m_selAI = num;
	m_AImode = AImode;

	for (int i = 0; i < 12; i++)
	{
		m_python[i] = py[i];
		if (py[i] == L'\0')
		{
			break;
		}
		else if (i == 11)
		{
			m_python[i - 1] = L'~';
			m_python[i] = L'\0';
		}
	}
	g_AIset[m_num].AInum = m_selAI;
	g_AIset[m_num].AImode = AImode;

	CVector3 spos = m_mon->GetPosition();
	CVector2 pos;
	pos.x = spos.x - 90;
	pos.y = spos.y - 68;
	pos.y = spos.y - 130;

	m_fr->Init(m_python, pos, 0, CVector4::White, 1, { 0.5f,0.5f });
	m_frShadow->Init(m_python, { pos.x + 5,pos.y - 5 }, 0, { 0,0,0,1 }, 1, { 0.5f,0.5f });
}

void PMMonster::yesSelect()
{
	m_issel = true;
	m_frame->Init(L"Assets/sprite/mon_frame.dds", 128, 128);
}

void PMMonster::notSelect()
{
	m_issel = false;
	m_frame->Init(L"Assets/sprite/mon_none.dds", 128, 128);
}

void PMMonster::PostRender()
{
	//font.Begin();

	

	//font.End();
}
