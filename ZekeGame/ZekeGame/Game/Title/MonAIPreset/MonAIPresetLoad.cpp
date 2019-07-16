#include "stdafx.h"
#include "MonAIPresetLoad.h"
#include "MonAIPresetSave.h"

#include "MonAIPreset.h"

#include "../PMMonster.h"
#include "../SuperMonsterSelect.h"
#include "../../GameCursor.h"

#include "../../GameData.h"

#include <locale>

void MonAIPresetLoad::OnDestroy()
{
	DeleteGO(m_font);
	DeleteGO(m_button);
}

bool MonAIPresetLoad::Start()
{
	m_button = NewGO<SpriteRender>(15, "sp");
	m_button->Init(L"Assets/sprite/fade_black.dds", 40, 30, true);
	m_button->SetPosition(m_pos);

	m_font = NewGO<FontRender>(15, "fr");
	m_font->SetTextType(CFont::en_Japanese);
	m_font->Init(L"開く", { m_pos.x,m_pos.y }, 0, CVector4::White, 1, { 0.5f,0.5f });
	return true;
}

void MonAIPresetLoad::init(SuperMonsterSelect* sms, int num,int team, GameCursor* cursor,MonAIPreset* mapr)
{
	m_sms = sms;
	m_num = num;
	m_team = team;
	m_cursor = cursor;
	m_map = mapr;
}

void MonAIPresetLoad::Update()
{
	m_button->SetCollisionTarget(m_cursor->GetCursor());
	if (m_button->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;

			FILE* file = fopen("Assets/MonAIPreset/preset.amp", "r");
			if (file == NULL)
			{
				return;
			}
			char head[5] = { 0 };
			fread(head, 4, 1, file);
			if (strcmp(head, "AMPS") != 0)
				return;
			chank chn[3];
			for (int i = 0; i < m_num+1; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					char ch[255];
					fread(&chn[j].monID, 1, 1, file);
					fread(&chn[j].stlen, 4, 1, file);
					fread(ch, chn[j].stlen, 1, file);
					/*chn[j].str = (char*)malloc(sizeof(char)*(strlen(ch) + 1));
					char[strlen(ch) + 1];*/
					strcpy(chn[j].str, ch);
				}
			}

			fclose(file);
			int ind[3] = {0};
			int i = 0;
			for (auto c : chn)
			{
				
				int count = 0;
				for (auto py : m_sms->GetFiles())
				{
					
					if (c.str == py)
					{
						ind[i] = count;
						break;
					}
					count++;
				}
				i++;
			}

			i = 0;
			for (auto pmm : m_sms->GetPMMonster())
			{
				if (m_team == pmm->Getteam())
				{
					wchar_t ws[255];
					setlocale(LC_ALL, "japanese");
					size_t size = 0;
					mbstowcs_s(&size, ws, 20, chn[i].str,_TRUNCATE);
					//todo: 俺 AIModeをフォーマットに追加
					pmm->SetPython(ws, ind[i],0);
					
					pmm->ChengeImage((MonsterID)chn[i].monID);
				}
				i++;
			}
			m_map->Close();
		}
	}

}
