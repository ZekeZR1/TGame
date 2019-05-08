#include "stdafx.h"
#include "MonAIPresetOpenSuper.h"

#include "../SuperMonsterSelect.h"
#include "../../GameCursor.h"

#include "MonAIPresetSave.h"

#include "MonAIPresets.h"

Preset MonAIPresetOpenSuper::m_presets[6];
std::map<int, int> MonAIPresetOpenSuper::m_aimap;
bool MonAIPresetOpenSuper::m_isAllNone;
MonAIPresetOpenSuper::~MonAIPresetOpenSuper()
{
	DeleteGO(m_button);
	DeleteGO(m_font);
}

bool MonAIPresetOpenSuper::Start()
{
	return true;
}

void MonAIPresetOpenSuper::init(SMS * sms, GameCursor * cursor, const wchar_t* tx,CVector3 pos, int team)
{
	m_sms = sms;
	m_cursor = cursor;
	m_team = team;

	m_button = NewGO<SpriteRender>(1, "sp");
	m_button->Init(L"Assets/sprite/fade_black.dds", 200, 60);
	m_button->SetPivot({ 0.f,0.5f });
	m_button->SetPosition(pos);

	m_dummy = NewGO<SpriteRender>(0, "sp");
	m_dummy->Init(L"", 200, 60, true);
	m_dummy->SetPivot({ 0.f,0.5f });
	m_dummy->SetPosition(pos);

	m_font = NewGO<FontRender>(2, "fr");
	m_font->SetTextType(CFont::en_Japanese);
	pos.y += 10;
	m_font->Init(tx, pos.ToTwo(), 0, CVector4::White, 0.7f, { 0,0 });
	m_font->DrawShadow();

	FILE* file = fopen("Assets/MonAIPreset/preset.amp", "r");
	if (file == NULL)
	{
		initPreset();
		file = fopen("Assets/MonAIPreset/preset.amp", "r");
	}
	char head[5] = { 0 };
	fread(head, 4, 1, file);
	if (strcmp(head, "AMPS") != 0)
		return;

	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		Preset chn;
		for (int j = 0; j < 3; j++)
		{
			char ch[255];
			fread(&chn.person[j].monID, 1, 1, file);
			fread(&chn.person[j].stlen, 4, 1, file);
			fread(ch, chn.person[j].stlen, 1, file);
			/*chn[j].str = (char*)malloc(sizeof(char)*(strlen(ch) + 1));
			char[strlen(ch) + 1];*/
			strcpy(chn.person[j].str, ch);

			if (chn.person[j].monID == 0)
				count++;
		}
		m_presets[i] = chn;
	}
	if (count == 18)
		m_isAllNone = true;

	fclose(file);
	

	for (int prc = 0;prc < 6;prc++)
	{
		for (int cc = 0;cc < 3;cc++)
		{
			int count = 0;
			int hash = CUtil::MakeHash(m_presets[prc].person[cc].str);
			if (m_aimap.count(hash))
			{
				int index = m_aimap.at(hash);
				m_presets[prc].person[cc].stind = index;
			}
			else for (auto py : m_sms->GetFiles())
			{
				
				if (m_presets[prc].person[cc].str == py)
				{
					m_presets[prc].person[cc].stind = count;
					m_aimap.insert(std::make_pair(hash, count));
					//i++;
					break;
				}
				count++;
			}
			
		}
	}

}

void MonAIPresetOpenSuper::Update()
{
	if (m_isOpen)
	{
		int num = m_maps->GetClickNum();
		if (num < 6)
		{
			Execute(num);
			//Close();
		}
		else if (Mouse::isTrigger(enLeftClick))
		{
			//Close();
		}
	}
}

void MonAIPresetOpenSuper::UpdateEx()
{
	m_isClick = false;
	if (m_type == enLoader && m_isAllNone)
		m_button->SetMulCol({ 0.2f,0.2f, 0.2f, 1.f });
	else
		m_button->SetMulCol({ 1.f,1.f, 1.f, 1.f });

	m_dummy->SetCollisionTarget(m_cursor->GetCursor());
	if (m_dummy->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;

		}

		if (!m_isSelect)	//マウスオーバー時のアクション
		{

			m_isSelect = true;
		}
	}
	else
	{
		if (m_isSelect)		//notマウスオーバー時のアクション
		{

			m_isSelect = false;
		}
	}
	
}

void MonAIPresetOpenSuper::Open()
{
	if (m_type == enLoader && m_isAllNone)
		return;
	FindPreset();

	m_back = NewGO<SpriteRender>(2, "sp");
	m_back->Init(L"Assets/sprite/B_alpha.dds", 1280, 720);

	FILE* file = FindPreset();
	char head[5] = { 0 };
	fread(head, 4, 1, file);
	if (strcmp(head, "AMPS") != 0)
		return;

	for (int i = 0; i < 6; i++)
	{
		Preset chn;
		for (int j = 0; j < 3; j++)
		{
			char ch[255];
			fread(&chn.person[j].aimode, 1, 1, file);
			fread(&chn.person[j].monID, 1, 1, file);
			fread(&chn.person[j].stlen, 4, 1, file);
			fread(ch, chn.person[j].stlen, 1, file);
			/*chn[j].str = (char*)malloc(sizeof(char)*(strlen(ch) + 1));
			char[strlen(ch) + 1];*/
			strcpy(chn.person[j].str, ch);
		}
		m_presets[i] = chn;
	}

	fclose(file);
	int i = 0;

	for (auto pre : m_presets)
	{
		for (auto c : pre.person)
		{
			int hash = CUtil::MakeHash(c.str);
			int count = 0;
			if (m_aimap.count(hash))
			{
				int index = m_aimap.at(hash);
				c.stind = index;
			}
			else for (auto py : m_sms->GetFiles())
			{

				if (c.str == py)
				{
					c.stind = i;
					m_aimap.insert(std::make_pair(hash, count));
					break;
				}
				count++;
			}
			i++;
		}
	}

	m_maps = NewGO<MonAIPresets>(0, "maps");
	m_maps->init(this,m_cursor);

	m_isOpen = true;
}

void MonAIPresetOpenSuper::Close()
{
	DeleteGO(m_back);

	DeleteGO(m_maps);
	m_first = true;

	m_isOpen = false;
}

FILE* MonAIPresetOpenSuper::FindPreset()
{
	FILE* file = fopen("Assets/MonAIPreset/preset.amp", "r");
	if (file != NULL)
	{
		return file;
	}
	return initPreset();
}

FILE* MonAIPresetOpenSuper::initPreset()
{
	FILE* file = fopen("Assets/MonAIPreset/preset.amp", "wb");
	
	fwrite("AMPS", 4, 1, file);//ヘッダー
	for (int i = 0; i < 6; i++)
	{
		for (int c = 0; c < 3; c++)
		{
			int z = 0;
			int o = 1;
			fwrite(&z, 1, 1, file);//AIの種類 0はpython 1はVisualAI
			fwrite(&z, 1, 1, file);//モンスターの種類
			fwrite(&o, 4, 1, file);//ファイルの文字数
			fwrite(&z, 1, 1, file);//ファイル名
		}
	}

	//fclose(file);
	return file;
}
