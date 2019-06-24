#include "stdafx.h"
#include "MonsterSelect.h"
#include "PMMonster.h"
#include "AIMSelect.h"
#include "../GameData.h"
#include "../GameCursor.h"
#include "IconMon.h"
#include <string>

#include "../MonsterBox/MonsterBox.h"
//#include "../GameData.h"

#include "AISelect.h"

MonsterSelect::~MonsterSelect()
{
	DeleteGO(m_back);
	for (auto ic : m_icons)
	{
		DeleteGO(ic);
	}
	DeleteGO(m_monsel);
	DeleteGO(m_title);
	DeleteGO(m_check);
}

bool MonsterSelect::Start()
{
	m_monsel = NewGO<SpriteRender>(28, "sp");
	m_monsel->Init(L"Assets/sprite/Monselect.dds", 570, 84);
	m_monsel->SetPivot({ 0,1 });
	m_monsel->SetPosition({ -246,360,0 });

	m_title = NewGO<FontRender>(28, "fr");
	m_title->SetTextType(CFont::en_Japanese);
	m_title->Init(L"モンスターセレクト", { -246,348 }, 0, { 1,1,1,1 }, 1.25f);
	m_title->DrawShadow();

	m_cursor = FindGO<GameCursor>("cursor");

	m_back = NewGO<SpriteRender>(2, "sp");
	m_back->Init(L"Assets/sprite/mon_back.dds", m_backsize.x * 4, m_backsize.y * 5,true);
	m_back->SetPivot({ 0,1 });
	CVector3 pos = { -257,360,0 };
	//CVector3 pos = { -257,230.5f,0 };
	m_back->SetPosition(pos);

	pos += { 78,-78,0 };
	pos.y = 205.0f;
	m_monstercount = enNumMonster;
	//for (int i = 1; i < m_monstercount; i++)
	int count = 0;
	for (int i = 0; i < m_monstercount; i++)
	{
		if (!IMonsterBox().isGot((MonsterID)i))
			continue;
		IconMon* im = NewGO<IconMon>(0, "im");
		//std::wstring path;

		im->init(GameData::GetMonsterIconPath(i),m_cursor);

		im->SetMonID(i);

		im->Setpos(pos);
		//if (((i+1) % 5) == 0)
		if (((count + 1) % 4) == 0)
		{
			pos.x = -179;
			pos.y -= 133;
		}
		else pos += {137, 0, 0};//pos += {133,0, 0};
		m_icons.push_back(im);
		//m_paths.push_back(path);.

		count++;
	}
	m_maxScroll = pos.y*-1;

	//NewGO<AISelect>(0, "ais");

	m_check = NewGO<SpriteRender>(6, "sr");
	m_check->Init(L"Assets/sprite/check.dds", 128, 128);
	m_check->SetPosition({ 3000,0,0 });
	return true;
}

void MonsterSelect::init(PMMonster * pmm,AIMSelect* aims)
{
	m_pmm = pmm;
	m_selmon = (MonsterID)m_pmm->GetMonsterID();

	m_aims = aims;
}

void MonsterSelect::Update()
{
	//Mouse::GetMouseNotch();

	for (int i = 0;i < m_icons.size();i++)
	{
		if (m_icons[i]->isClick())
		{
			//todo:monsel debug
			//m_aims->Setmon(i+1);
			m_aims->Setmon(m_icons[i]->GetMonID());

			m_check->SetPosition(m_icons[i]->Getpos());
			//m_pmm->ChengeImage(m_paths[i].c_str(),i);
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
				float vNotch = notch * 50;
				m_scroll += vNotch;
				
				
				for (auto icon : m_icons)
				{
					CVector3 pos = icon->Getpos();
					pos.y += vNotch;
					icon->Setpos(pos);
				}
				CVector3 cp = m_check->GetPosition();
				cp.y += vNotch;
				m_check->SetPosition(cp);
			}
			i++;

		}
		else
			i = 0;
	}
}
