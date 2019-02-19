#include "stdafx.h"
#include "AISelect.h"
#include "PMMonster.h"
#include "AIMSelect.h"
#include <string>
#include "SuperMonsterSelect.h"
#include "pvpModeSelect.h"
#include "../GameCursor.h"
#include "IconAI.h"

AISelect::~AISelect()
{
	DeleteGO(m_back);
	for (auto ia : m_icons)
	{
		DeleteGO(ia);
	}
	DeleteGO(m_AIsel);
}

bool AISelect::Start()
{
	m_AIsel = NewGO<SpriteRender>(27, "sp");
	m_AIsel->Init(L"Assets/sprite/AIselect.dds", 371, 84);
	m_AIsel->SetPivot({ 0,1 });
	m_AIsel->SetPosition({ -640,360,0 });

	m_cursor = FindGO<GameCursor>("cursor");

	m_back = NewGO<SpriteRender>(5, "sp");
	m_back->Init(L"Assets/sprite/ai_back_R.dds", 383, 720,true);
	m_back->SetPosition({ -448.5f,0,0});
	
	m_ppms = FindGO<SuperMonsterSelect>("pvp");
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
	return true;
}

void AISelect::init(PMMonster * pmm,AIMSelect* aims)
{
	m_pmm = pmm;
	m_AIMS = aims;
}

void AISelect::Update()
{
	for (int i = 0;i < m_icons.size();i++)
	{
		if (m_icons[i]->isClick())
		{
			m_AIMS->SetAI(i);
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
				m_scroll += notch * 50;
				CVector3 pos = m_icons[0]->Getpos();
				pos.y = m_scroll;
				for (auto icon : m_icons)
				{
					icon->Setpos(pos);
					pos.y -= 82.0f;
				}
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
