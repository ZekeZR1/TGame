#include "stdafx.h"
#include <string>
#include "DungeonGame.h"
#include "DungeonSelect.h"
#include "../Title/ModeSelect.h"
#include "../Fade/Fade.h"
#include "../GameData.h"
#include "../GameCursor.h"
#include "../Title/SuperMonsterSelect.h"
#include "../StageSetup/StageSetup.h"
#include "../Game.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "../StageSetup/StageSelect.h"
#include "../Title/ModeSelect.h"
#include "../Title/PMMonster.h"
#include "DungeonAISelect.h"
#include "DungeonTransition.h"

#include "../ReturnButton/ReturnButton.h"
#include "../Title/MonAIPreset/MonAIPresetOpenSuper.h"
#include "../Title/MonAIPreset/MonAIPresetSaveOpen.h"
#include "../Title/MonAIPreset/MonAIPresetLoadOpen.h"

DungeonAISelect::DungeonAISelect()
{
}


DungeonAISelect::~DungeonAISelect()
{
	
}

void DungeonAISelect::OnDestroy()
{
	DeleteGO(m_dunSp);
	DeleteGO(m_font);
	DeleteGO(m_cursor);
	for (auto go : m_pmms)
	{
		DeleteGO(go);
	}
	DeleteGO(m_GO);
	DeleteGO(m_backSp);
	DeleteGO(m_returnButton);
	DeleteGO(m_msp);
	DeleteGO(m_mlp);
}

bool DungeonAISelect::Start() {
	auto m_BGM = FindGO<Sound>("BGM");
	if (m_BGM == nullptr)
	{
		m_BGM = NewGO<Sound>(0, "BGM");
		m_BGM->Init(L"Assets/sound/BGM/PerituneMaterial_Strategy5_loop.wav", true);
		m_BGM->Play();
	}
	//m_backSp->Init(L"Assets/Sprite/dungeonAiSelectWallpaper.dds", 1280.f, 720.f, false);
	m_backSp = NewGO<SpriteRender>(0, "sp");
	m_backSp->Init(L"Assets/sprite/monsel_back.dds", 1280, 720);

	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	m_files = PythonFileLoad::FilesLoad();
	m_enemyFiles = PythonFileLoad::FilesLoadEnemy();
	m_cursor = NewGO<GameCursor>(0, "cursor");
	CVector3 pos = { -320,0,0 };
	for (int i = 0; i < m_numPmm; i++) {
		m_pmms.push_back(NewGO<PMMonster>(0, "pmm"));
		m_pmms[i]->init(i, pos);
		pos.x += 240.f;
		if (g_AIset[i].AImode == 0) //AImode Python
		{
			std::wstring ws = std::wstring(m_files[g_AIset[i].AInum].begin(), m_files[g_AIset[i].AInum].end());
			m_pmms[i]->SetPython(ws.c_str(), g_AIset[i].AInum, g_AIset[i].AImode);
		}
		else //AImode VisualAI
		{
			wchar_t ws[3]; 
			swprintf_s(ws, L"%d", g_AIset[i].AInum);
			m_pmms[i]->SetPython(ws, g_AIset[i].AInum, g_AIset[i].AImode);
		}
	}
	m_GO = NewGO<SpriteRender>(1, "sp");
	m_GO->Init(L"Assets/sprite/GO.dds", 193, 93, true);
	m_GO->SetPosition({ 400,-160,0 });
	m_dunSp = NewGO<SpriteRender>(1, "dunSp");
	m_dunSp->Init(L"Assets/Sprite/DadandanBk.dds", 350.f, 70.f);
	m_dunSp->SetPosition({ 0.f,300.f,0.f });
	m_font = NewGO<FontRender>(1, "font");
	m_font->SetTextType(CFont::en_Japanese);
	wchar_t dungeon[256];
	swprintf_s(dungeon, L"ダンジョン%d\n", m_dunNum + 1);
	m_font->Init(dungeon, { -140.f, 320.f }, 0.f, CVector4::White, 1.f, { 0.f,0.f });


	m_returnButton = NewGO<ReturnButton>(1, "rb");
	m_returnButton->init(this, "pvp", m_cursor);

	//　紅組用のチームを保存するやつ
	m_msp = NewGO<MonAIPresetSaveOpen>(0, "mapso");
	m_msp->init(this, m_cursor, L"チームを保存", { 410,130,0 }, 0);
	//　紅組用のチームを開くやつ
	m_mlp = NewGO<MonAIPresetLoadOpen>(0, "maplo");
	m_mlp->init(this, m_cursor, L"チームを開く", { 410,60,0 }, 0);
	return true;
}

void DungeonAISelect::Update() {
	bool ismonsel = false;
	int count = 0;
	bool ispmm = false;
	for (auto pmm : m_pmms)
	{
		ispmm = pmm->isOpen();
		if (ispmm)
			break;
	}
	if (ispmm)
		return;
	
	/*for (auto pmm : m_pmms)
	{
		if (pmm->isClick())
		{
			pmm->Open();
		}
	}*/
	/*for (auto pmm : m_pmms)
	{
		ismonsel = pmm->isMonSel();
		if (ismonsel || pmm->isSelect())
		{
			break;
		}
		count++;
	}*/
	if (ismonsel)
		return;
	if (!(m_msp->IsOpen() || m_mlp->IsOpen()))
	{
		m_msp->UpdateEx();
		m_mlp->UpdateEx();

		if (m_msp->IsClick())
		{
			m_msp->Open();
		}
		else if (m_mlp->IsClick())
		{
			m_mlp->Open();
		}

		for (auto pmm : m_pmms)
		{
			pmm->UpdateEX();
		}
			

		m_GO->SetCollisionTarget(m_cursor->GetCursor());
		if (m_GO->isCollidingTarget())
		{
			if (Mouse::isTrigger(enLeftClick))
			{
				for (int i = 0; i < m_numPmm; i++)
				{
					moid[i] = static_cast<MonsterID>(m_pmms[i]->GetMonsterID());
					monai[i] = m_pmms[i]->GetAI();
				}
				m_fade->FadeOut();
				m_isfade = true;
			}
		}
		if (m_isfade && m_fade->isFadeStop()) {
			auto dun = NewGO<DungeonGame>(0, "DungeonGame");
			int i = 0;
			for (auto p : m_pmms) {
				aimode[i] = p->GetAImode();
				i++;
			}
			dun->SetGameData(m_files, m_enemyFiles, monai, moid, m_dunNum, aimode);
			OutputDebugStringA("AI Selected!! Start Transation!\n");
			dun->StartTransition();
			DeleteGO(this);
		}

		m_returnButton->UpdateEx<DungeonSelect>();

		//	m_backSp->SetCollisionTarget(m_cursor->GetCursor());
		////	if (g_pad[0].IsTrigger(enButtonA)) {
		//	if(m_backSp->isCollidingTarget() && Mouse::isTrigger(enLeftClick)){
		//		m_fade->FadeOut();
		//		isfade = true;
		//	}
	}
	if (isfade && m_fade->isFadeStop()) {
		NewGO<DungeonSelect>(0, "DungeonSelect");
		auto dgame = FindGO<DungeonGame>("DungeonGame");
		DeleteGO(this);
		DeleteGO(dgame);
	}
	
}

void DungeonAISelect::LoadFiles() {
	HANDLE hfind;
	WIN32_FIND_DATA win32d;
	std::vector<std::string> filenames;

	char c[255];
	std::string cd;
	GetCurrentDirectory(255, c);
	cd = c;

	std::string key = cd + "/PythonAIs/*.py";
	hfind = FindFirstFile(key.c_str(), &win32d);

	do
	{
		if (win32d.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
		}
		else
		{
			std::string p = win32d.cFileName;
			p.resize(p.length() - 3);
			m_files.push_back(p);

		}
	} while (FindNextFile(hfind, &win32d));
	FindClose(hfind);
}


std::vector<std::string> DungeonAISelect::GetFiles() {
	return m_files;
}
