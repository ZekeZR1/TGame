#include "stdafx.h"
#include "AISelect.h"
#include "PMMonster.h"
#include "AIMSelect.h"
#include <string>
#include "SuperMonsterSelect.h"
#include "pvpModeSelect.h"
#include "../GameCursor.h"
#include "IconAI.h"

#include "../AIEdit/VisualAIOpen.h"

AISelect::~AISelect()
{
	DeleteGO(m_back);
	for (auto ia : m_icons)
	{
		DeleteGO(ia);
	}
	DeleteGO(m_AIsel);
	DeleteGO(m_changeAI);
	DeleteGO(m_CAfont);

	DeleteGO(m_title);
	DeleteGO(m_check);
}

bool AISelect::Start()
{
	m_AIsel = NewGO<SpriteRender>(29, "sp");
	m_AIsel->Init(L"Assets/sprite/AIselect.dds", 371, 84);
	m_AIsel->SetPivot({ 0,1 });
	m_AIsel->SetPosition({ -640,360,0 });

	m_title = NewGO<FontRender>(29, "fr");
	//m_title->SetTextType(CFont::en_JapaneseBIG);
	m_title->Init(L"VisualAI", { -640,360 }, 0, { 1,1,1,1 }, 1.f);
	m_title->DrawShadow();
	

	m_cursor = FindGO<GameCursor>("cursor");

	m_back = NewGO<SpriteRender>(5, "sp");
	m_back->Init(L"Assets/sprite/ai_back_R.dds", 383, 720,true);
	m_back->SetPosition({ -448.5f,0,0});
	
	m_ppms = FindGO<SuperMonsterSelect>("pvp");
	int count = m_ppms->GetFiles().size();

	CreateViAI();

	/*CVector3 pos = { -454,316.5f,0 };
	pos = { -454,230.5f,0 };
	for (int i = 0; i < count; i++)
	{
		IconAI* ia = NewGO<IconAI>(0, "ia");
		std::string st = m_ppms->GetFiles()[i];
		ia->init(st, i, m_cursor);
		ia->Setpos(pos);
		m_icons.push_back(ia);

		pos.y -= 82;
	}
	m_minScroll = 316.5f;
	m_minScroll = 230.5f;
	m_maxScroll = pos.y * -1;*/
	m_scroll = m_minScroll;


	//切り替えボタンの表示
	m_changeAI = NewGO<SpriteRender>(29, "sp");
	m_changeAI->Init(L"Assets/sprite/PVchenger_V.dds", 80, 38.5f, true);
	m_changeAI->SetPosition({ -350,330,0 });
	m_changeAI->SetPivot({ 0,1 });

	/*m_CAfont = NewGO<FontRender>(29, "fr");
	m_CAfont->Init(L"visAI", { -420,320 },0,CVector4::White,0.5f);
	m_CAfont->DrawShadow();*/

	m_check = NewGO<SpriteRender>(27, "sp");
	m_check->Init(L"Assets/sprite/check.dds", 80, 80);
	m_check->SetPosition({ 3000,0,0 });
	
	return true;
}

void AISelect::init(PMMonster * pmm,AIMSelect* aims)
{
	m_pmm = pmm;
	m_AIMS = aims;
}

void AISelect::Update()
{
	////AIの切り替えボタンの処理
	m_changeAI->SetCollisionTarget(m_cursor->GetCursor());
	if (m_changeAI->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			DeleteAI();
			m_check->SetPosition({ 3000,0,0 });
			m_scroll = m_minScroll;
			switch (m_AImode)
			{
			case enPy:
				CreateViAI();
				m_AImode = enVi;
				m_changeAI->Init(L"Assets/sprite/PVchenger_V.dds", 80, 38.5f, true);
				m_title->Init(L"VisualAI", { -640,360 }, 0, { 1,1,1,1 }, 1.0f);
				break;
			case enVi:
				CreatePyAI();
				m_AImode = enPy;
				m_changeAI->Init(L"Assets/sprite/PVchenger_P.dds", 80, 38.5f, true);
				m_title->Init(L"PythonAI", { -640,360 }, 0, { 1,1,1,1 }, 1.f);
				break;
			}
		}
	}
	////


	for (int i = 0;i < m_icons.size();i++)
	{
		if (m_icons[i]->isClick())
		{
			if (m_AImode == enVi)
			{
				i = m_icons[i]->getVisualAIname();
			}
			m_AIMS->SetAI(i,m_AImode);

			CVector3 cp = m_icons[i]->Getpos();
			cp.x += 130;
			m_check->SetPosition(cp);
			break;
			/*std::string st = m_ppms->GetFiles()[i];
			std::wstring ws = std::wstring(st.begin(), st.end());
			m_pmm->SetPython(ws.c_str(),i);*/

		}
	}
	m_back->SetCollisionTarget(m_cursor->GetCursor());
	if (m_back->isCollidingTarget())
	{
		static int i = 0;
		int notch = Mouse::GetMouseNotch() * -1;
		if (notch != 0)
		{
			
			if (i >= 2)
				int a = 0;
			if (!(m_scroll <= m_minScroll && notch < 0) && !(m_scroll >= m_maxScroll && notch > 0))
			{
				int ntc = notch * 50;
				m_scroll += ntc;
				for (auto icon : m_icons)
				{
					CVector3 pos = icon->Getpos();
				
					
					pos.y += ntc;
					icon->Setpos(pos);
				}
				CVector3 cp = m_check->GetPosition();
				cp.y += ntc;
				m_check->SetPosition(cp);
			}
			i++;

		}
		else
			i = 0;
	}
}

void AISelect::PostRender()
{


	//font.Begin();
	/*for (int i = 0; i < m_icons.size(); i++)
	{
		CVector3 pos = m_icons[i]->Getpos();

		std::string st = m_ppms->GetFiles()[i];
		std::wstring ws = std::wstring(st.begin(), st.end());

		font.Draw(ws.c_str(), { 0,pos.y }, CVector4::White, 0, 1, { 0,1 });
		m_fr->Init(ws.c_str(), { 0,pos.y },0, CVector4::White, 1, { 0,1 });
	}*/

	//font.End();
}

void AISelect::CreatePyAI()
{
	int count = m_ppms->GetFiles().size();

	CVector3 pos = { -454,316.5f,0 };
	pos = { -454,230.5f,0 };
	for (int i = 0; i < count; i++)
	{
		IconAI* ia = NewGO<IconAI>(0, "ia");
		std::string st = m_ppms->GetFiles()[i];
		ia->init(st, i, m_cursor);
		ia->Setpos(pos);
		m_icons.push_back(ia);

		pos.y -= 82;
	}
	m_minScroll = 316.5f;
	m_minScroll = 230.5f;
	m_maxScroll = pos.y * -1;
}



void AISelect::CreateViAI()
{
	std::vector<VisualAIState> vas = VisualAIOpen::openVAs();
	int count = vas.size();

	CVector3 pos = { -454,316.5f,0 };
	pos = { -454,230.5f,0 };
	for (int i = 0; i < count; i++)
	{
		IconAI* ia = NewGO<IconAI>(0, "ia");
		char c[25];
		sprintf(c, "%d", vas[i].num);
		std::string st = c;
		ia->init(st, i, m_cursor,true,vas[i].mark);
		ia->Setpos(pos);
		m_icons.push_back(ia);

		pos.y -= 82;
	}
	m_minScroll = 316.5f;
	m_minScroll = 230.5f;
	m_maxScroll = pos.y * -1;
}

void AISelect::DeleteAI()
{
	for (auto icon : m_icons)
	{
		DeleteGO(icon);

	}
	m_icons.clear();
	m_icons.shrink_to_fit();
}