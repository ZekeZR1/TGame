#include "stdafx.h"
#include "VisualAIOpen.h"

CVector4 VisualAIOpen::mRed = { 0.9f,0.4f,0.4f,1 };
CVector4 VisualAIOpen::mBlu = { 0.4f,0.4f,0.9f,1 };
CVector4 VisualAIOpen::mYel = { 0.9f,0.9f,0.4f,1 };
CVector4 VisualAIOpen::mWhi = { 0.9f,0.9f,0.9f,1 };

std::vector<VisualAIState> VisualAIOpen::openVAs()
{
	HANDLE hfind;
	WIN32_FIND_DATA win32d;


	char cs[255];
	std::string cd;
	GetCurrentDirectory(255, cs);
	cd = cs;
	
	std::string path = cd + "\\Assets\\VisualAI\\";

	std::string key = path + "*.va";
	hfind = FindFirstFile(key.c_str(), &win32d);

	std::vector< VisualAIState> vass;
	int count = 0;
	while (FindNextFile(hfind, &win32d) && count < 12)
	{
		if (win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		}
		else
		{
			VisualAIState vas;

			std::string p = win32d.cFileName;
			
			//ファイル名から番号を抽出する
			int c = p.find(".");
			char n[3] = {'\0'};
			for (int i = 0; i < c; i++)
			{
				n[i] = p[i];
				
			}
			int num = atoi(n);

			////ファイル名から色の部分を抽出する
			//char cl[4] = { '\0' };
			//for (int i = 0; i < 3; i++)
			//{
			//	cl[i] = p[i + c + 1];
			//}

			////色を決定する
			//CVector4 col;
			//if (strcmp("red", cl) == 0)
			//{
			//	col = mRed;
			//}
			//else if (strcmp("blu", cl) == 0)
			//{
			//	col = mBlu;
			//}
			//else if (strcmp("yel", cl) == 0)
			//{
			//	col = mYel;
			//}
			//else
			//{
			//	col = mWhi;
			//}

			std::string filename = path + p;
			FILE* file = fopen(filename.c_str(), "rb");
			char he[6] = {'\0'};
			fread(&he, 5, 1, file);
			fseek(file, 1, SEEK_CUR);
			int i = 0;
			fread(&i, 1, 1, file);
			fclose(file);

			CVector4 col;
			switch (i)
			{
			case 0:
				col = mRed;
				break;
			case 1:
				col = mBlu;
				break;
			case 2:
				col = mYel;
				break;
			case 3:
				col = mWhi;
				break;
			}

			vas.num = num;
			vas.col = col;
			vas.mark = i;
			vas.file = p;

			vass.push_back(vas);
			count++;
		}
	} 
	FindClose(hfind);
	return vass;
}
