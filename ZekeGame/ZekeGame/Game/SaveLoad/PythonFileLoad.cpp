#include "stdafx.h"
#include "PythonFileLoad.h"

#include <string>

std::vector<std::string> PythonFileLoad::FilesLoad()
{
	HANDLE hfind;
	WIN32_FIND_DATA win32d;
	std::vector<std::string> filenames;


	char c[255];
	std::string cd;
	GetCurrentDirectory(255, c);
	cd = c;

	std::string key = cd + "\\PythonAIs\\*.py*";
	hfind = FindFirstFile(key.c_str(), &win32d);


	//è¡Ç∑
	//FontRender* font = NewGO<FontRender>(0, "font");
	//std::wstring ws = std::wstring(key.begin(), key.end());
	//font->Init(ws.c_str(), { -620,0 }, 0, CVector4::Yellow, 1, { 0.5f,0.5f });

	do
	{
		if (win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		}
		else
		{
			std::string p = win32d.cFileName;
			if (p == "_MiddleExecute.py" || p == "CppBridge.py")
				continue;
				
			//p.resize(p.length() - 3);
			p.resize(p.rfind('.'));
			filenames.push_back(p);

		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
	return filenames;
}

std::vector<std::string> PythonFileLoad::FilesLoadEnemy()
{
	HANDLE hfind;
	WIN32_FIND_DATA win32d;
	std::vector<std::string> filenames;


	char c[255];
	std::string cd;
	GetCurrentDirectory(255, c);
	cd = c;

	std::string key = cd + "\\PythonEnemyAIs\\*.py*";
	hfind = FindFirstFile(key.c_str(), &win32d);


	//è¡Ç∑
	//FontRender* font = NewGO<FontRender>(0, "font");
	//std::wstring ws = std::wstring(key.begin(), key.end());
	//font->Init(ws.c_str(), { -620,0 }, 0, CVector4::Yellow, 1, { 0.5f,0.5f });

	do
	{
		if (win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		}
		else
		{
			std::string p = win32d.cFileName;
			if (p == "_MiddleExecute.py" || p == "CppBridge.py")
				continue;
			//p.resize(p.length() - 3);
			p.resize(p.rfind('.'));
			filenames.push_back(p);

		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
	return filenames;
}


std::vector<std::string> PythonFileLoad::FilesLoadOnlineEnemy()
{
	HANDLE hfind;
	WIN32_FIND_DATA win32d;
	std::vector<std::string> filenames;


	char c[255];
	std::string cd;
	GetCurrentDirectory(255, c);
	cd = c;

	std::string key = cd + "\\NetworkEnemyAIs\\*.py*";
	hfind = FindFirstFile(key.c_str(), &win32d);

	OutputDebugString("LOAD NETWORK ENEMY AIS \n");
	//è¡Ç∑
	//FontRender* font = NewGO<FontRender>(0, "font");
	//std::wstring ws = std::wstring(key.begin(), key.end());
	//font->Init(ws.c_str(), { -620,0 }, 0, CVector4::Yellow, 1, { 0.5f,0.5f });

	do
	{
		if (win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		}
		else
		{
			std::string p = win32d.cFileName;
			if (p == "_MiddleExecute.py" || p == "CppBridge.py")
				continue;
			//p.resize(p.length() - 3);
			p.resize(p.rfind('.'));
			filenames.push_back(p);

		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
	return filenames;
}


std::vector<std::string> VisualAiFileLoad::FilesLoad() {
	using namespace std;
	HANDLE hfind;
	WIN32_FIND_DATA win32d;
	vector<string> filenames;

	char c[255];
	std::string cd;
	GetCurrentDirectory(255, c);
	cd = c;

	std::string key = cd + "\\Assets\\VisualAI\\*.va*";
	hfind = FindFirstFile(key.c_str(), &win32d);

	do
	{
		if (win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		}
		else
		{
			std::string p = win32d.cFileName;
			p.resize(p.rfind('.'));
			filenames.push_back(p);
		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
	return filenames;
}