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

DungeonAISelect::DungeonAISelect()
{
}


DungeonAISelect::~DungeonAISelect()
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
}

bool DungeonAISelect::Start() {
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
		std::wstring ws = std::wstring(m_files[g_AIset[i].AInum].begin(), m_files[g_AIset[i].AInum].end());
		m_pmms[i]->SetPython(ws.c_str(), g_AIset[i].AInum, g_AIset[i].AImode);
	}
	m_GO = NewGO<SpriteRender>(0, "sp");
	m_GO->Init(L"Assets/sprite/GO.dds", 193, 93, true);
	m_GO->SetPosition({ 400,-160,0 });
	m_dunSp = NewGO<SpriteRender>(0, "dunSp");
	m_dunSp->Init(L"Assets/Sprite/DadandanBk.dds", 350.f, 70.f);
	m_dunSp->SetPosition({ 0.f,300.f,0.f });
	m_font = NewGO<FontRender>(0, "font");
	m_font->SetTextType(CFont::en_Japanese);
	wchar_t dungeon[256];
	swprintf_s(dungeon, L"ƒ_ƒ“ƒWƒ‡ƒ“%d\n", m_dunNum + 1);
	m_font->Init(dungeon, { -140.f, 320.f }, 0.f, CVector4::White, 1.f, { 0.f,0.f });
	m_backSp = NewGO<SpriteRender>(0);
	m_backSp->Init(L"Assets/Sprite/returnButton.dds", 200.f, 50.f, true);
	CVector3 p = { -430.f,-300.f,0.f };
	m_backSp->SetPosition(p);
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
	for (auto pmm : m_pmms)
	{
		if (pmm->isClick())
		{
			pmm->Open();
		}
	}
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
		dun->SetGameData(m_files, m_enemyFiles, monai, moid, m_dunNum,aimode);
		OutputDebugStringA("AI Selected!! Start Transation!\n");
		dun->StartTransition();
		DeleteGO(this);
	}
	m_backSp->SetCollisionTarget(m_cursor->GetCursor());
//	if (g_pad[0].IsTrigger(enButtonA)) {
	if(m_backSp->isCollidingTarget() && Mouse::isTrigger(enLeftClick)){
		m_fade->FadeOut();
		isfade = true;
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
