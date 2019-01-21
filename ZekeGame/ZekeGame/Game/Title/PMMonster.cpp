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
}

PMMonster::PMMonster()
{
	m_mon = NewGO<SpriteRender>(1, "sp");
	m_mon->Init(L"Assets/sprite/mon_one.dds", 128, 128,true);
	
	m_frame = NewGO<SpriteRender>(0, "sp");
	m_frame->Init(L"Assets/sprite/mon_none.dds", 128, 128);
}

bool PMMonster::Start()
{
	m_fr = NewGO<FontRender>(0, "font");
	m_cursor = FindGO<GameCursor>("cursor");
	return true;
}

void PMMonster::init(int num,CVector3 pos)
{
	m_num = num;
	m_mon->SetPosition(pos);
	m_frame->SetPosition(pos);

	ChengeImage(nullptr, g_monset[m_num]);
}

void PMMonster::Update()
{
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
			m_frame->Init(L"Assets/sprite/mon_frame.dds", 128, 128);
			m_issel = true;
		}
		if (Mouse::isTrigger(enLeftClick))
		{
			AIMSelect* aims = NewGO<AIMSelect>(0, "aims");
			aims->init(this, m_selAI, m_monid);
			/*m_ms = NewGO<MonsterSelect>(0, "monsterselect");
			m_ais = NewGO<AISelect>(0, "aiselect");
			m_ms->init(this);
			m_ais->init(this);*/
			m_ismonsel = true;
		}
	}
	else
	{
		if (m_issel && issel)
		{
			m_frame->Init(L"Assets/sprite/mon_none.dds", 128, 128);
			m_issel = false;
		}
	}
}

void PMMonster::ChengeImage(const wchar_t* path, int monid)
{
	/*wchar_t ws[255] ;
	GameData::GetMonsterIconPath(ws, monid);
	m_mon->Init(ws, 128, 128);
	m_monid = (MonsterID)monid;
	delete[] ws;*/
	m_monid = (MonsterID)monid;
	switch (monid)
	{
	case enTest:
		m_mon->Init(L"Assets/sprite/mon_one.dds", 128, 128);
		break;
	case enUmataur:
		m_mon->Init(L"Assets/sprite/mon_two.dds", 128, 128);
		break;
	}

	g_monset[m_num] = monid;
	//m_path = path;
}

void PMMonster::SetPython(const wchar_t * py,int num)
{
	m_selAI = num;

	for (int i = 0; i < 16; i++)
	{
		m_python[i] = py[i];
		if (py[i] == L'\0')
		{
			break;
		}
		else if (i == 15)
		{
			m_python[i - 1] = L'~';
			m_python[i] = L'\0';
		}
	}
	g_AIset[m_num] = m_selAI;
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

	CVector3 spos = m_mon->GetPosition();
	CVector2 pos;
	pos.x = spos.x-90;
	pos.y = spos.y-68;

	//font.Draw(m_python, pos);
	m_fr->Init(m_python, pos, 0, CVector4::White, 1, { 0.5f,0.5f });

	//font.End();
}
