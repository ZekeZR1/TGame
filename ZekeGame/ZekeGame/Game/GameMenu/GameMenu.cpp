#include "stdafx.h"
#include "GameMenu.h"

#include "../Game.h"
#include "../GameCursor.h"

#include "../Fade/MusicFade.h"

#include "../Title/ModeSelect.h"
#include "../Title/pvpModeSelect.h"
#include "../Dungeon/DungeonAISelect.h"

#include "MenuButton.h"
#include "../Dungeon/DungeonGame.h"

#include "../NetPVP/NetAISelect.h"

#include "../Fade/Fade.h"

GameMenu::~GameMenu()
{
	
}

void GameMenu::OnDestroy()
{
	DeleteGO(m_cursor);
	if (m_isOpen)
	{
		for (auto go : m_buttons)
			DeleteGO(go);
	}
	//auto game = FindGO<Game>("Game");
}

void GameMenu::Release()
{
	
}

bool GameMenu::Start()
{
	m_game = FindGO<Game>("Game");
	m_fade = FindGO<Fade>("fade");
	return true;
}

void GameMenu::Update()
{
	if (!m_isdo)
		return;
	if (m_isFade)
	{
		if (m_fade->isFadeStop())
		{
			switch (m_bnum)
			{
			case 0:
				DeleteGO(m_game);
				DeleteGO(this);
				if (m_game->GetGameMode() == Game::enDungeon)
					DeleteGO(FindGO<DungeonGame>("DungeonGame"));
				NewGO<ModeSelect>(0, "modesel");
				break;
			case 1:
				DeleteGO(m_game);
				DeleteGO(this);

				switch (m_playMode)
				{
				case Game::enLocalPVP:
					NewGO<PvPModeSelect>(0, "pvp");
					break;
				case Game::enDungeon:
				{
					if (m_game->GetGameMode() == Game::enDungeon)
						DeleteGO(FindGO<DungeonGame>("DungeonGame"));
					DungeonAISelect * DAS = NewGO<DungeonAISelect>(0, "pvp");
					DAS->SetDungeonNumber(m_dunnum);
					break;
				}
				case Game::enRandomPVP:
					NetAISelect* netpvp = NewGO<NetAISelect>(0, "pvp");
					break;
				}

				break;
			}
		}
	}
	else if (m_isOpen)
	{
		for (int i = 0;i < m_buttons.size();i++)
		{
			if (m_buttons[i]->isClick())
			{
				
				switch (i)
				{
				case 0:
				case 1:
				{
					m_bnum = i;
					m_isFade = true;
					m_fade->FadeOut();
					MusicFade* mf = NewGO<MusicFade>(0, "mf");
					mf->init(FindGO<Sound>("BGM"), 1, 10);
					PlayButtonSE();
					break;
				}
				case 2:
					for (auto go : m_buttons)
						DeleteGO(go);
					m_buttons.clear();
					m_buttons.shrink_to_fit();
					DeleteGO(m_cursor);
					m_cursor = nullptr;
					PlayButtonSE();

					m_isOpen = false;
					break;
				}
			}
		}
		if (g_pad[0].IsTrigger(enButtonStart) || g_pad[0].IsTrigger(enButtonB))
		{
			for (auto go : m_buttons)
				DeleteGO(go);
			m_buttons.clear();
			m_buttons.shrink_to_fit();
			DeleteGO(m_cursor);
			m_cursor = nullptr;
			PlayButtonSE();

			m_isOpen = false;
		}
	}
	else
	{
		if (g_pad[0].IsTrigger(enButtonStart) || g_pad[0].IsTrigger(enButtonSelect))
		{
			m_cursor = NewGO<GameCursor>(0, "cursor");
			CVector3 pos = { 0,200,0 };
			for (int i = 0; i < 3; i++)
			{
				CVector2 po2 = pos.ToTwo();
				po2.y += 25;
				FontRender* moji = NewGO<FontRender>(29, "sp");
				moji->SetTextType(CFont::en_JapaneseBIG);
				switch (i)
				{
				case 0:
					po2.x -= 133;
					moji->Init(L"タイトルへ", po2, 0, { 0.05f,0.05f, 0.05f, 1 }, 0.3f);
					break;
				case 1:
					po2.x -= 159;
					moji->Init(L"キャラ選択へ", po2, 0, { 0.05f,0.05f, 0.05f, 1 }, 0.3f);
					break;
				case 2:
					po2.x -= 83;
					moji->Init(L"とじる", po2, 0, { 0.05f,0.05f, 0.05f, 1 }, 0.3f);
					break;
				}
				MenuButton* button = NewGO<MenuButton>(0, "mb");
				button->init(m_cursor, pos,moji);
				m_buttons.push_back(button);

				pos.y -= 110;
			}
			PlayButtonSE();

			m_isOpen = true;
		}
	}
}
