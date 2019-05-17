#include "stdafx.h"
#include "MonsterSelect.h"
#include "PMMonster.h"
#include "AIMSelect.h"
#include "../GameData.h"
#include "../GameCursor.h"
#include "IconMon.h"
#include <string>
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
}

bool MonsterSelect::Start()
{
	m_monsel = NewGO<SpriteRender>(28, "sp");
	m_monsel->Init(L"Assets/sprite/Monselect.dds", 570, 84);
	m_monsel->SetPivot({ 0,1 });
	m_monsel->SetPosition({ -246,360,0 });

	m_title = NewGO<FontRender>(28, "fr");
	m_title->SetTextType(CFont::en_Japanese);
	m_title->Init(L"モンスターセレクト", { -246,340 }, 0, { 1,1,1,1 }, 1.25f);
	m_title->DrawShadow();

	m_cursor = FindGO<GameCursor>("cursor");

	m_back = NewGO<SpriteRender>(2, "sp");
	m_back->Init(L"Assets/sprite/mon_back.dds", m_backsize.x * 4, m_backsize.y * 5);
	m_back->SetPivot({ 0,1 });
	CVector3 pos = { -257,360,0 };
	//CVector3 pos = { -257,230.5f,0 };
	m_back->SetPosition(pos);

	pos += { 78,-78,0 };
	pos.y = 205.0f;
	m_monstercount = enNumMonster;
	//for (int i = 1; i < m_monstercount; i++)
	for (int i = 0; i < m_monstercount; i++)
	{
		IconMon* im = NewGO<IconMon>(0, "im");
		//std::wstring path;

		im->init(GameData::GetMonsterIconPath(i),m_cursor);

		/*switch (i)
		{
		case enTest:
			im->init(L"Assets/sprite/mon_one.dds",m_cursor);
			path = L"Assets/sprite/mon_one.dds";
			break;
		case enUmataur:
			im->init(L"Assets/sprite/mon_two.dds", m_cursor);
			path = L"Assets/sprite/mon_two.dds";
			break;
		case enFairy:
			im->init(L"Assets/sprite/mon_three.dds", m_cursor);
			path = L"Assets/sprite/mon_three.dds";
			break;
		}*/
		im->Setpos(pos);
		if ((i+1 % 5) == 0)
		{
			pos.x = 30;
			pos.y -= 133;
		}
		else pos += {133,0, 0};
		m_icons.push_back(im);
		//m_paths.push_back(path);
	}

	//NewGO<AISelect>(0, "ais");
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
			m_aims->Setmon(i+1);
			//m_pmm->ChengeImage(m_paths[i].c_str(),i);
		}
	}
}
