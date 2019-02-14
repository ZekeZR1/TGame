// my name is pvp.


#include "stdafx.h"
#include "SuperMonsterSelect.h"
#include "pvpModeSelect.h"


#include <string>
#include "../GameCursor.h"

#include "ModeSelect.h"

#include "../StageSetup/StageSetup.h"
#include "../Game.h"

#include "../SaveLoad/PythonFileLoad.h"

#include "PMMonster.h"

PvPModeSelect::~PvPModeSelect()
{
	DeleteGO(m_cursor);
	for (auto go : m_pmms)
	{
		DeleteGO(go);
	}
	DeleteGO(m_GO);
	DeleteGO(m_back);
}

bool PvPModeSelect::Start()
{
	m_back = NewGO<SpriteRender>(0, "sp");
	m_back->Init(L"Assets/sprite/monsel_back.dds", 1280, 720);

	m_files = PythonFileLoad::FilesLoad();
	m_cursor = NewGO<GameCursor>(0, "cursor");
	
	CVector3 pos = { -290,180,0 };
	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
		{
			pos = { -290,-180,0 };
		}
		PMMonster* pmm = NewGO<PMMonster>(0, "pmm");
		pmm->init(i,pos);
		pos += {260, 0, 0};
		std::wstring ws = std::wstring(m_files[g_AIset[i]].begin(), m_files[g_AIset[i]].end());
		pmm->SetPython(ws.c_str(), g_AIset[i]);
		m_pmms.push_back(pmm);
	}
	//m_pmm = NewGO<PMMonster>(0, "pmm");
	//m_pmm->init({ -250,-200,0 });
	for (int i = 0; i < 6; i++)
	{
		/*SpriteRender* sp = NewGO<SpriteRender>(0, "sp");
		sp->Init(L"Assets/sprite/mon",);*/
	}

	m_GO = NewGO<SpriteRender>(0, "sp");
	m_GO->Init(L"Assets/sprite/GO.dds", 193, 93, true);
	m_GO->SetPosition({ 520,240,0 });

	return true;
}

void PvPModeSelect::Update()
{
	bool ismonsel = false;
	int count = 0;
	for (auto pmm : m_pmms)
	{
		ismonsel = pmm->isMonSel();
		if (ismonsel || pmm->isSelect())
		{
			break;
		}

		count++;
	}
	if (ismonsel)
		return;
	m_GO->SetCollisionTarget(m_cursor->GetCursor());
	if (m_GO->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			MonsterID moid[6];
			for (int i = 0;i < 6;i++)
			{
				moid[i] = (MonsterID)m_pmms[i]->GetMonsterID();
				monai[i] = m_pmms[i]->GetAI();
			}
			Game* game = NewGO<Game>(0, "Game");
			////game->GamePVPmodeInit(m_files, monai,moid);
			StageSetup::PVPSetup(m_files,monai,moid);
			DeleteGO(this);
		}
	}

	
	if (count == 6)
	{
		count = 0;
	}
	if (!ismonsel)
	{
		if (g_pad[0].IsTrigger(enButtonB))
		{
		}
		else if (g_pad[0].IsTrigger(enButtonDown))
		{
			if (count < 3)
			{
				m_pmms[count]->notSelect();
				count += 3;
				m_pmms[count]->yesSelect();
			}
		}
		else if (g_pad[0].IsTrigger(enButtonUp))
		{
			if (count > 2)
			{
				m_pmms[count]->notSelect();
				count -= 3;
				m_pmms[count]->yesSelect();
			}
		}
		else if (g_pad[0].IsTrigger(enButtonLeft))
		{
			if (count != 0 && count != 3)
			{
				m_pmms[count]->notSelect();
				count--;
				m_pmms[count]->yesSelect();
			}
		}
		else if (g_pad[0].IsTrigger(enButtonRight))
		{
			if (count != 2 && count != 5)
			{
				m_pmms[count]->notSelect();
				count++;
				m_pmms[count]->yesSelect();
			}
		}
	}

	if (g_pad[0].IsTrigger(enButtonA))
	{
		if (curpos == 6)
		{
			Game* game = NewGO<Game>(0, "Game");
			//game->GamePVPmodeInit(m_files, monai);.
			
			DeleteGO(this);
		}
		else if (!sel)
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
			NewGO<ModeSelect>(0, "modesel");
			DeleteGO(this);
		}
		else if (g_pad[0].IsTrigger(enButtonDown))
		{
			if (curpos < 5+1)
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
			if (monai[curpos] < m_files.size()-1)
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
			m_files.push_back(p);
			
		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
}

void PvPModeSelect::PostRender()
{
	/*CVector4 colors[7];
	for (CVector4& col : colors)
	{
		col = CVector4::White;
	}
	if(sel)
		colors[curpos] = CVector4::Yellow;
	else
		colors[curpos] = CVector4::Red;
	CVector2 pos = { -520,10};
	font.Begin();
	for (int i = 0; i < 7; i++)
	{
		if (i == 3)
		{
			pos = { -30,10 };
		}
		else if (i == 6)
		{
			pos = { 320,-210, };
			font.Draw(L"GO!", pos, colors[i],0,2);
			break;
		}
		std::wstring ws = std::wstring(m_files[monai[i]].begin(), m_files[monai[i]].end());
		font.Draw(ws.c_str(), pos, colors[i]);

		pos.y -= 50;
	}
	font.End();*/
}
