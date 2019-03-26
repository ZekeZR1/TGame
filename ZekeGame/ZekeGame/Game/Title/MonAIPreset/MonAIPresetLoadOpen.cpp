#include "stdafx.h"
#include "MonAIPresetLoadOpen.h"

#include "../SuperMonsterSelect.h"
#include "../PMMonster.h"

MonAIPresetLoadOpen::MonAIPresetLoadOpen()
{
	m_type = enLoader;
}

void MonAIPresetLoadOpen::Execute(int num)
{
	//FILE* file = fopen("Assets/MonAIPreset/preset.amp", "r");
	//if (file == NULL)
	//{
	//	return;
	//}
	//char head[5] = { 0 };
	//fread(head, 4, 1, file);
	//if (strcmp(head, "AMPS") != 0)
	//	return;
	//Person chn[3];
	//for (int i = 0; i < num + 1; i++)
	//{
	//	for (int j = 0; j < 3; j++)
	//	{
	//		char ch[255];
	//		fread(&chn[j].monID, 1, 1, file);
	//		fread(&chn[j].stlen, 4, 1, file);
	//		fread(ch, chn[j].stlen, 1, file);
	//		/*chn[j].str = (char*)malloc(sizeof(char)*(strlen(ch) + 1));
	//		char[strlen(ch) + 1];*/
	//		strcpy(chn[j].str, ch);
	//	}
	//}

	//fclose(file);


	int ind[3] = { 0 };
	int i = 0;

	for (int cc = 0; cc < 3; cc++)
	{
		int count = 0;
		int hash = CUtil::MakeHash(m_presets[num].person[cc].str);
		if (m_aimap.count(hash))
		{
			int index = m_aimap.at(hash);
			m_presets[num].person[cc].stind = index;
		}
		else for (auto py : m_sms->GetFiles())
		{

			if (m_presets[num].person[cc].str == py)
			{
				m_presets[num].person[cc].stind = count;
				m_aimap.insert(std::make_pair(hash, count));
				//i++;
				break;
			}
			count++;
		}

	}

	/*for (auto c : chn)
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
	}*/
	if (m_presets[num].person->monID == 0)
	{
		return;
	}

	i = 0;
	for (auto pmm : m_sms->GetPMMonster())
	{
		if (m_team == pmm->Getteam())
		{
			wchar_t ws[255];
			setlocale(LC_ALL, "japanese");
			size_t size = 0;
			//mbstowcs_s(&size, ws, 20, chn[i].str, _TRUNCATE);
			mbstowcs_s(&size, ws, 20, m_presets[num].person[i].str, _TRUNCATE);
			pmm->SetPython(ws, m_presets[num].person[i].stind);

			pmm->ChengeImage((MonsterID)m_presets[num].person[i].monID);
			i++;
		}
		
	}
	Close();
}
