#include "stdafx.h"
#include "AIMSelect.h"

#include "../GameCursor.h"
#include "SuperMonsterSelect.h"
#include "pvpModeSelect.h"
#include "PMMonster.h"

#include "AISelect.h"
#include "MonsterSelect.h"

AIMSelect::~AIMSelect()
{
	DeleteGO(m_AIS);
	DeleteGO(m_MS);
	DeleteGO(m_can);
	DeleteGO(m_cdum);
	DeleteGO(m_ok);
	DeleteGO(m_odum);
	DeleteGO(m_Black);
}

bool AIMSelect::Start()
{
	m_ppms = FindGO<SuperMonsterSelect>("pvp");
	m_cursor = FindGO<GameCursor>("cursor");

	m_AIS = NewGO<AISelect>(0, "ais");
	m_AIS->init(m_pmm, this);
	m_MS = NewGO<MonsterSelect>(0, "ms");
	m_MS->init(m_pmm, this);

	m_ok = NewGO<SpriteRender>(10, "sp");
	m_ok->Init(L"Assets/sprite/sb_OK.dds", 151, 64,true);
	m_odum = NewGO<SpriteRender>(9, "sp");
	m_odum->Init(L"Assets/sprite/simple_button.dds", 151, 64);
	CVector3 pos = { 411,-320,0 };
	m_ok->SetPosition(pos);
	m_odum->SetPosition(pos);

	m_can = NewGO<SpriteRender>(10, "sp");
	m_can->Init(L"Assets/sprite/sb_cancel.dds", 151, 64,true);
	m_cdum = NewGO<SpriteRender>(9, "sp");
	m_cdum->Init(L"Assets/sprite/simple_button.dds", 151, 64);
	pos = { 563,-320,0 };
	m_can->SetPosition(pos);
	m_cdum->SetPosition(pos);

	m_Black = NewGO<SpriteRender>(2, "sp");
	m_Black->Init(L"Assets/sprite/B_alpha.dds", 1280, 720);
	return true;
}

void AIMSelect::Update()
{
	CVector3 cpos = m_cursor->GetCursor();
	m_can->SetCollisionTarget(cpos);
	if (m_can->isCollidingTarget())
	{
		if(!m_isselC)
			m_cdum->Init(L"Assets/sprite/simple_button_blue.dds", 151, 64);
		if (Mouse::isTrigger(enLeftClick))
		{
			m_pmm->notMonSel();
			m_pmm->Close();
			DeleteGO(this);
		}
		m_isselC = true;
	}
	else
	{
		if (m_isselC)
			m_cdum->Init(L"Assets/sprite/simple_button.dds", 151, 64);
		m_isselC = false;
	}

	m_ok->SetCollisionTarget(cpos);
	if (m_ok->isCollidingTarget())
	{
		if(!m_isselO)
			m_odum->Init(L"Assets/sprite/simple_button_blue.dds", 151, 64);
		if (Mouse::isTrigger(enLeftClick))
		{
			std::string st;
			if (m_AImode == 0)//AI Mode‚ªpython‚ÌŽž
			{
				st = m_ppms->GetFiles()[m_ainum];
				std::wstring ws = std::wstring(st.begin(), st.end());
				m_pmm->SetPython(ws.c_str(), m_ainum, m_AImode);
			}
			else
			{
				wchar_t wai[64];
				swprintf_s(wai, L"%d", m_ainum);
				std::wstring ws = wai;
				m_pmm->SetPython(ws.c_str(), m_ainum, m_AImode);
			}
			

			m_pmm->ChengeImage(m_monnum);

			m_pmm->notMonSel();
			m_pmm->Close();
			DeleteGO(this);
		}
		m_isselO = true;
	}
	else
	{
		if (m_isselO)
			m_odum->Init(L"Assets/sprite/simple_button.dds", 151, 64);
		m_isselO = false;
	}
}
