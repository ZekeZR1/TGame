// ����modesel

#include "stdafx.h"
#include "ModeSelect.h"

#include "pvpModeSelect.h"
#include "AIeditModeSelect.h"
#include "../Dungeon/DungeonSelect.h"
#include "../../GameCamera.h"
#include "../GameCursor.h"


ModeSelect::~ModeSelect()
{
	//for (auto sp : m_selection)
	//{
	//	DeleteGO(sp);
	//}

	for (auto b : m_buttons)
	{
		delete b;
	}
	m_buttons.clear();
	m_buttons.shrink_to_fit();

	DeleteGO(m_back);
}

bool ModeSelect::Start()
{
	m_cursor = NewGO<GameCursor>(0, "cursor");

	m_back = NewGO<SpriteRender>(0, "sp");
	m_back->Init(L"Assets/sprite/modesel_back.dds", 1280, 720);


	/*CVector3 vadd = { 25,100,0 };
	vadd *= -1;
	CVector3 pos = m_standardpos;
	SpriteRender* sp;
	

	pos = m_standardpos + vadd * enDungeon;
	sp = NewGO<SpriteRender>(0, "ui");
	sp->Init(L"Assets/Sprite/dungeonW.dds", 400, 100);
	sp->SetPosition(pos);
	m_selection.push_back(sp);

	pos = m_standardpos + vadd*enLocalpvp;
	sp = NewGO<SpriteRender>(0, "ui");
	sp->Init(L"Assets/Sprite/localpvpG.dds", 400, 100);
	sp->SetPosition(pos);
	m_selection.push_back(sp);

	pos = m_standardpos + vadd * enRandompvp;
	sp = NewGO<SpriteRender>(0, "ui");
	sp->Init(L"Assets/Sprite/randompvpG.dds", 400, 100);
	sp->SetPosition(pos);
	m_selection.push_back(sp);

	pos = m_standardpos + vadd * enAIedit;
	sp = NewGO<SpriteRender>(0, "ui");
	sp->Init(L"Assets/Sprite/AIeditG.dds", 400, 100);
	sp->SetPosition(pos);
	m_selection.push_back(sp);*/


	button *b;
	CVector3 pos = { 360,250,0 };
	CVector3 add = { 0,(m_bSize.y + 20)*-1,0 };

	b = new button();
	b->frame->SetPosition(pos);
	b->moji->Init(L"Assets/sprite/modesel_dung.dds",m_bSize.x, m_bSize.y);
	b->moji->SetPosition(pos);
	m_buttons.push_back(b);
	pos += add;

	b = new button();
	b->frame->SetPosition(pos);
	b->moji->Init(L"Assets/sprite/modesel_local.dds", m_bSize.x, m_bSize.y);
	b->moji->SetPosition(pos);
	m_buttons.push_back(b);
	pos += add;

	b = new button();
	b->frame->SetPosition(pos);
	b->moji->Init(L"Assets/sprite/modesel_world.dds", m_bSize.x, m_bSize.y);
	b->moji->SetPosition(pos);
	m_buttons.push_back(b);
	pos += add;

	b = new button();
	b->frame->SetPosition(pos);
	b->moji->Init(L"Assets/sprite/modesel_aiedi.dds", m_bSize.x, m_bSize.y);
	b->moji->SetPosition(pos);
	m_buttons.push_back(b);

	return true;
}

void ModeSelect::Update()
{
	/*if (g_pad[0].IsTrigger(enButtonA))
	{
		switch (m_sel)
		{
		case enDungeon:
			NewGO<DungeonSelect>(0, "dan");
			DeleteGO(this);
			break;
		case enLocalpvp:
			NewGO<PvPModeSelect>(0, "pvp");
			DeleteGO(this);
			break;
		case enRandompvp:
			break;
		case enAIedit:
			NewGO<AIEditModeSelect>(0, "AIedit");
			DeleteGO(this);
			break;
		}
	}
	else if (g_pad[0].IsTrigger(enButtonDown))
	{
		if (m_sel < m_selection.size() - 1)
		{
			switch (m_sel)
			{
			case enDungeon:
				m_selection[enDungeon]->Init(L"Assets/Sprite/dungeonG.dds", 400, 100);
				m_selection[enLocalpvp]->Init(L"Assets/Sprite/localpvpW.dds", 400, 100);
				break;
			case enLocalpvp:
				m_selection[enLocalpvp]->Init(L"Assets/Sprite/localpvpG.dds", 400, 100);
				m_selection[enRandompvp]->Init(L"Assets/Sprite/randompvpW.dds", 400, 100);
				break;
			case enRandompvp:
				m_selection[enRandompvp]->Init(L"Assets/Sprite/randompvpG.dds", 400, 100);
				m_selection[enAIedit]->Init(L"Assets/Sprite/AIeditW.dds", 400, 100);
				break;
			case enAIedit:
				break;
			}
			m_sel++;
			
		}

	}
	else if (g_pad[0].IsTrigger(enButtonUp))
	{
		if (m_sel > 0)
		{
			switch (m_sel)
			{
			case enDungeon:
				break;
			case enLocalpvp:
				m_selection[enDungeon]->Init(L"Assets/Sprite/dungeonW.dds", 400, 100);
				m_selection[enLocalpvp]->Init(L"Assets/Sprite/localpvpG.dds", 400, 100);
				break;
			case enRandompvp:
				m_selection[enLocalpvp]->Init(L"Assets/Sprite/localpvpW.dds", 400, 100);
				m_selection[enRandompvp]->Init(L"Assets/Sprite/randompvpG.dds", 400, 100);
				break;
			case enAIedit:
				m_selection[enRandompvp]->Init(L"Assets/Sprite/randompvpW.dds", 400, 100);
				m_selection[enAIedit]->Init(L"Assets/Sprite/AIeditG.dds", 400, 100);
				break;
			}
			m_sel--;
		}
	}*/




	CVector3 curpos = m_cursor->GetCursor();
	int count = 0;
	for (auto button : m_buttons)
	{
		SpriteRender* frame = button->frame;
		frame->SetCollisionTarget(curpos);
		if (frame->isCollidingTarget())
		{
			if (!button->isCursor)
			{
				button->isCursor = true;
				CVector3 pos = frame->GetPosition();
				pos.x -= 40;
				frame->SetPosition(pos);
				button->moji->SetPosition(pos);
				m_count = count;

				switch (count)
				{
				case enDungeon:
					m_back->Init(L"Assets/sprite/modesel_back_dung.dds", 1280, 720);
					break;
				case enLocalpvp:
					m_back->Init(L"Assets/sprite/modesel_back_local.dds", 1280, 720);
					break;
				case enRandompvp:
					break;
				case enAIedit:
					break;
				}
			}
			if (Mouse::isTrigger(enLeftClick))
			{
				switch (count)
				{
				case enDungeon:
					NewGO<DungeonSelect>(0, "dan");
					DeleteGO(this);
					break;
				case enLocalpvp:
					NewGO<PvPModeSelect>(0, "pvp");
					DeleteGO(this);
					break;
				case enRandompvp:
					break;
				case enAIedit:
					NewGO<AIEditModeSelect>(0, "AIedit");
					DeleteGO(this);
					break;
				}
			}
		}
		else
		{
			if (button->isCursor && m_count != count)
			{
				button->isCursor = false;
				CVector3 pos = frame->GetPosition();
				pos.x += 40;
				frame->SetPosition(pos);
				button->moji->SetPosition(pos);

			}
		}

		count++;
	}


}