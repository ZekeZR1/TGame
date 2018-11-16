#include "stdafx.h"
#include "pvpModeSelect.h"
#include <string>

bool PvPModeSelect::Start()
{
	LoadFiles();
	return false;
}

void PvPModeSelect::Update()
{
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

}
