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

#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"

#include "../ReturnButton/ReturnButton.h"
#include "..//ToAiEditModeButton.h"

//#include "MonAIPreset/MonAIPresetSave.h"
//#include "MonAIPreset/MonAIPresetLoad.h"
//#include "MonAIPreset/MonAIPresetOpen.h"

#include "MonAIPreset/MonAIPresetOpenSuper.h"
#include "MonAIPreset/MonAIPresetSaveOpen.h"
#include "MonAIPreset/MonAIPresetLoadOpen.h"

#include "GObutton.h"

#include "MonsterSelectBack.h"

PvPModeSelect::~PvPModeSelect()
{
	
}

void PvPModeSelect::OnDestroy()
{
	DeleteGO(m_cursor);
	for (auto go : m_pmms)
	{
		DeleteGO(go);
	}
	//DeleteGO(m_GO);
	DeleteGO(m_back);
	DeleteGO(m_return);
	DeleteGO(m_returnMoji);
	//DeleteGO(m_mapo);

	DeleteGO(m_msRed);
	DeleteGO(m_mlRed);
	DeleteGO(m_msBlue);
	DeleteGO(m_mlBlue);
	DeleteGO(m_aibutton);

	DeleteGO(m_returnButton);
	DeleteGO(m_GOb);

	DeleteGO(m_msb);
}

bool PvPModeSelect::Start()
{
	m_BGM = FindGO<Sound>("BGM");
	if (m_BGM == nullptr)
	{
		m_BGM = NewGO<Sound>(0,"BGM");
		m_BGM->Init(L"Assets/sound/BGM/PerituneMaterial_Strategy5_loop.wav", true);
		m_BGM->SetVolume(m_vol);
		m_BGM->Play();
	}
	m_aibutton = NewGO< ToAiEditModeButton>(0);
	m_aibutton->SetCurrentScene(this);
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	//m_back = NewGO<SpriteRender>(0, "sp");
	//m_back->Init(L"Assets/sprite/monsel_back.dds", 1280, 720);

	m_msb = NewGO<MonsterSelectBack>(0, "msb");

	m_files = PythonFileLoad::FilesLoad();
	m_cursor = NewGO<GameCursor>(0, "cursor");



	//　紅組用のチームを保存するやつ
	m_msRed = NewGO<MonAIPresetSaveOpen>(0, "mapso");
	m_msRed->init(this, m_cursor, L"チームを保存", { 410,130,0 }, 0);
	//　紅組用のチームを開くやつ
	m_mlRed = NewGO<MonAIPresetLoadOpen>(0, "maplo");
	m_mlRed->init(this, m_cursor, L"チームを開く", { 410,60,0 }, 0);

	//　AO組用のチームを保存するやつ
	m_msBlue = NewGO<MonAIPresetSaveOpen>(0, "mapso");
	m_msBlue->init(this, m_cursor, L"チームを保存", { 410,-230,0 }, 1);
	//　AO組用のチームを開くやつ
	m_mlBlue = NewGO<MonAIPresetLoadOpen>(0, "maplo");
	m_mlBlue->init(this, m_cursor, L"チームを開く", { 410,-300,0 }, 1);
	
	CVector3 pos = { -290,180,0 };
	for (int i = 0; i < 6; i++)
	{
		if (i == 3)
		{
			pos = { -290,-180,0 };
		}
		PMMonster* pmm = NewGO<PMMonster>(0, "pmm");
		pmm->init(i,pos);
		pmm->Setteam(i >= 3);
		pos += {260, 0, 0};
		if (g_AIset[i].AImode == 0) //AImode python
		{
			std::wstring ws = std::wstring(m_files[g_AIset[i].AInum].begin(), m_files[g_AIset[i].AInum].end());
			pmm->SetPython(ws.c_str(), g_AIset[i].AInum, g_AIset[i].AImode);
		}
		else //AImode visualAI
		{
			wchar_t ws[3];
			swprintf_s(ws, L"%d", g_AIset[i].AInum);
			pmm->SetPython(ws, g_AIset[i].AInum, g_AIset[i].AImode);
		}
		m_pmms.push_back(pmm);
	}

	CVector3 repo = { -520,-260,0 };

	m_returnButton = NewGO<ReturnButton>(0, "rb");
	m_returnButton->init(this, "modesel", m_cursor);

	m_GOb = NewGO<GObutton>(0, "gb");
	m_GOb->init(m_cursor, { 520,240,0 });

	return true;
}

void PvPModeSelect::Update()
{
	
	if (m_isfade)
	{
		if (m_fade->isFadeStop())
		{
			MonsterID moid[6];
			int AImodes[6];
			for (int i = 0; i < 6; i++)
			{
				moid[i] = (MonsterID)m_pmms[i]->GetMonsterID();
				monai[i] = m_pmms[i]->GetAI();
				AImodes[i] = m_pmms[i]->GetAImode();
			}
			Game* game = NewGO<Game>(0, "Game");
			////game->GamePVPmodeInit(m_files, monai,moid);
			StageSetup::PVPSetup(m_files, monai, moid,AImodes);
			//m_BGM->Stop();
			DeleteGO(this);
		}
		return;
	}

	bool ispmm = false;
	for (auto pmm : m_pmms)
	{
		ispmm = pmm->isOpen();
		if (ispmm)
			break;
	}

	static bool isopen = false;
	if (m_aibutton->isFading())
		return;
	//何か開いていた場合は他のものはクリックしても反応しない。
	if (!(m_msRed->IsOpen() || m_mlRed->IsOpen() || m_msBlue->IsOpen() || m_mlBlue->IsOpen() || ispmm || isopen))
	{
		m_returnButton->UpdateEx<ModeSelect>();
		m_aibutton->SetTarget(m_cursor->GetCursor());
		m_msRed->UpdateEx();
		m_mlRed->UpdateEx();
		m_msBlue->UpdateEx();
		m_mlBlue->UpdateEx();
		//プリセットのセーブ
		if (m_msRed->IsClick()) 
		{
			m_msRed->Open();
		}
		if (m_mlRed->IsClick())
		{
			m_mlRed->Open();
		}
		if (m_msBlue->IsClick())
		{
			m_msBlue->Open();
		}
		if (m_mlBlue->IsClick())
		{
			m_mlBlue->Open();
		}
		for (auto pmm : m_pmms)
		{
			pmm->UpdateEX();
		}


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

		m_GOb->UpdateEx();
		if (m_GOb->isClick())
		{
			m_fade->FadeOut();
			m_isfade = true;
			MusicFade* mf = NewGO<MusicFade>(0, "mf");
			mf->init(m_BGM, m_vol);
			PlayButtonSE();
		}
	}
	isopen = ispmm;
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
}
