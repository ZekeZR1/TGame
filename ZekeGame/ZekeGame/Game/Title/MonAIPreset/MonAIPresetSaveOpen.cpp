#include "stdafx.h"
#include "MonAIPresetSaveOpen.h"

#include "../SuperMonsterSelect.h"
#include "../PMMonster.h"

#include "../../GameCursor.h"

MonAIPresetSaveOpen::MonAIPresetSaveOpen()
{
	m_type = enSaver;
}

void MonAIPresetSaveOpen::Execute(int num)
{
	m_isAllNone = false;

	int ai[3];
	int mon[3];

	int count = 0;
	QueryGOs<PMMonster>("pmm", [&](PMMonster* go)->bool
	{
		if (go->Getteam() == m_team)
		{
			ai[count] = go->GetAI();
			mon[count] = go->GetMonsterID();
			count++;
		}
		return true;
	});

	FILE* file = fopen("Assets/MonAIPreset/preset.amp", "rb+");
	if (file == NULL)
	{
		file = fopen("Assets/MonAIPreset/preset.amp", "wb");
		fwrite("AMPS", 4, 1, file);
		for (int i = 0; i < 6; i++)
		{
			int zr = 0, bf = 2;
			for (int c = 0; c < 3; c++)
			{

				fwrite(&zr, 1, 1, file);
				fwrite(&bf, 4, 1, file);
				fwrite("a", 2, 1, file);
			}
		}
		fclose(file);
		file = fopen("Assets/MonAIPreset/preset.amp", "rb+");
	}
	//fwrite("AMPS", 4, 1, file);
	Person chn[6][3];
	fseek(file, 4, SEEK_CUR);
	int seek = 4;
	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			fread(&chn[r][c].monID, 1, 1, file);
			fread(&chn[r][c].stlen, 4, 1, file);
			fread(&chn[r][c].str, chn[r][c].stlen, 1, file);
			/*fseek(file, 1, SEEK_CUR);
			int i = 0;
			fread(&i, 4, 1, file);
			fseek(file, i, SEEK_CUR);*/
			if (r < num)
				seek += 1 + 4 + chn[r][c].stlen;
		}
	}
	//fclose(file);
	//file = fopen("Assets/MonAIPreset/preset.amp", "wb+");
	fseek(file, seek, SEEK_SET);
	for (int i = 0; i < 3; i++)
	{
		fwrite(&mon[i], 1, 1, file);
		std::string py = m_sms->GetFiles()[ai[i]];
		int len = py.length() + 1;
		fwrite(&len, 4, 1, file);
		fwrite(py.c_str(), len, 1, file);

	}
	for (int r = num + 1; r < 6; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			m_presets[r].person[c].monID = chn[r][c].monID;
			m_presets[r].person[c].stlen = chn[r][c].stlen;
			strcpy(m_presets[r].person[c].str, chn[r][c].str);
			m_presets[r].person[c].stind = ai[c];

			fwrite(&chn[r][c].monID, 1, 1, file);
			fwrite(&chn[r][c].stlen, 4, 1, file);
			fwrite(&chn[r][c].str, chn[r][c].stlen, 1, file);

			
		}
	}
	fclose(file);

	Close();
}
