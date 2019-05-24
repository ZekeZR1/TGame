#include "stdafx.h"
#include "GameMenu.h"

#include "../Game.h"
#include "../GameCursor.h"

#include "../Title/ModeSelect.h"
#include "../Title/pvpModeSelect.h"
#include "../Dungeon/DungeonAISelect.h"

#include "MenuButton.h"
#include "../Dungeon/DungeonGame.h"

GameMenu::~GameMenu()
{
	if (m_isOpen)
	{
		for (auto go : m_buttons)
			DeleteGO(go);
		
	}
}

void GameMenu::OnDestroy()
{
	DeleteGO(m_cursor);
	auto game = FindGO<Game>("Game");
}

void GameMenu::Release()
{
	
}

bool GameMenu::Start()
{
	
	return true;
}

void GameMenu::Update()
{
	if (!m_isdo)
		return;
	if (m_isOpen)
	{
		for (int i = 0;i < m_buttons.size();i++)
		{
			if (m_buttons[i]->isClick())
			{
				Game* game = FindGO<Game>("Game");
				switch (i)
				{
				case 0:
					DeleteGO(game);
					DeleteGO(this);
					if (game->GetGameMode() == Game::enDungeon)
						DeleteGO(FindGO<DungeonGame>("DungeonGame"));
					NewGO<ModeSelect>(0,"modesel");
					break;
				case 1:
					
					DeleteGO(game);
					DeleteGO(this);

					switch (m_playMode)
					{
					case Game::enLocalPVP:
						NewGO<PvPModeSelect>(0, "pvp");
						break;
					case Game::enDungeon:
						if (game->GetGameMode() == Game::enDungeon)
							DeleteGO(FindGO<DungeonGame>("DungeonGame"));
						DungeonAISelect* DAS = NewGO<DungeonAISelect>(0, "pvp");
						DAS->SetDungeonNumber(m_dunnum);
						break;
					}
					
					break;
				case 2:
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
				FontRender* moji = NewGO<FontRender>(29, "sp");
				switch (i)
				{
				case 0:
					moji->Init(L"タイトルへ", pos.ToTwo());
					break;
				case 1:
					moji->Init(L"キャラ選択へ", pos.ToTwo());
					break;
				case 2:
					moji->Init(L"とじる", pos.ToTwo());
					break;
				}
				MenuButton* button = NewGO<MenuButton>(0, "mb");
				button->init(m_cursor, pos,moji);
				m_buttons.push_back(button);

				pos.y -= 110;
			}

			m_isOpen = true;
		}
	}
}
