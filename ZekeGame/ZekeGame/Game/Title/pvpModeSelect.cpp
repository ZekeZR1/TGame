#include "stdafx.h"
#include "pvpModeSelect.h"
#include <string>

bool PvPModeSelect::Start()
{
	LoadFiles();
	return true;
}

void PvPModeSelect::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{
		if (!sel)
		{
			sel = true;
		}
		else
		{
			sel = false;
		}
	}
	if (!sel)
	{
		if (g_pad[0].IsTrigger(enButtonB))
		{

		}
		else if (g_pad[0].IsTrigger(enButtonDown))
		{
			if (curpos < 5)
			{
				curpos++;
			}
		}
		else if (g_pad[0].IsTrigger(enButtonUp))
		{
			if (curpos > 0)
			{
				curpos--;
			}
		}
	}
	else
	{
		if (g_pad[0].IsTrigger(enButtonLeft))
		{
			if (monai[curpos] > 0)
			{
				monai[curpos]--;
			}
		}
		else if (g_pad[0].IsTrigger(enButtonRight))
		{
			if (monai[curpos] < files.size()-1)
			{
				monai[curpos]++;
			}
		}
	}
}

void PvPModeSelect::LoadFiles()
{
	HANDLE hfind;
	WIN32_FIND_DATA win32d;
	std::vector<std::string> filenames;

	char c[255];
	std::string cd;
	GetCurrentDirectory(255, c);
	cd = c;

	std::string key = cd+"/PythonAIs/*.py";
	hfind = FindFirstFile(key.c_str(), &win32d);
	
	do
	{
		if(win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{ }
		else
		{
			std::string p = win32d.cFileName;
			p.resize(p.length() - 3);
			files.push_back(p);
			
		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
}

void PvPModeSelect::PostRender()
{
	CVector4 colors[6] = { CVector4::White };
	for (CVector4&col : colors)
	{
		col.x -= 0.0001f;
		col.y -= 0.0001f;
		col.z -= 0.0001f;
	}
	if(sel)
		colors[curpos] = CVector4::Yellow;
	else
		colors[curpos] = CVector4::Red;
	CVector3 pos = { 10,10,0 };
	for (int i = 0; i < 6; i++)
	{
		std::wstring ws = std::wstring(files[monai[i]].begin(), files[monai[i]].end());
		font.Init(ws.c_str(), pos, CVector3::One(), colors[i]);
		font.Draw();

		pos.y += 50;
	}
}
