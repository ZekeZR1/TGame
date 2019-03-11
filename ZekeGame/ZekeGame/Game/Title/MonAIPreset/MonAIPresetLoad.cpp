#include "stdafx.h"
#include "MonAIPresetLoad.h"
#include "MonAIPresetSave.h"

#include "../PMMonster.h"
#include "../SuperMonsterSelect.h"
#include "../../GameCursor.h"

bool MonAIPresetLoad::Start()
{
	m_button = NewGO<SpriteRender>(15, "sp");
	m_button->Init(L"Assets/sprite/fade_black.dds", 40, 30, true);
	m_button->SetPosition({ -540,270,0 });

	m_font = NewGO<FontRender>(15, "fr");
	m_font->SetTextType(CFont::en_Japanese);
	m_font->Init(L"ŠJ‚­", { -540,270 }, 0, CVector4::White, 1, { 0.5f,0.5f });
	return true;
}

void MonAIPresetLoad::init(SuperMonsterSelect* sms, int num, GameCursor* cursor)
{
	m_sms = sms;
	m_num = num;
	m_cursor = cursor;
}

void MonAIPresetLoad::Update()
{
	m_button->SetCollisionTarget(m_cursor->GetCursor());
	if (m_button->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			FILE* file = fopen("Assets/MonAIPreset/preset.amp", "r");
			if (file == NULL)
			{
				return;
			}
			char head[5];
			fread(head, 4, 1, file);
			if (strcmp(head, "AMPS") != 0)
				return;
			chank chn[3];
			for (int i = 0; i < m_num; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					fread(&chn[j].monID, 1, 1, file);
					fread(&chn[j].stlen, 4, 1, file);
					fread(&chn[j].str, chn[j].stlen, 1, file);
				}
			}


			fclose(file);
		}
	}

}
