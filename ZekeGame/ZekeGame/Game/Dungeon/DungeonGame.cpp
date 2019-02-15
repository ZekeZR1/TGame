#include "stdafx.h"
#include "../GameData.h"
#include "DungeonGame.h"
#include "DungeonData.h"
#include "DungeonTransition.h"


bool DungeonGame::Start() {
	return true;
}

void DungeonGame::OnDestroy() {

}

void DungeonGame::Update() {
}

void DungeonGame::SetGameData(PyFile& files, PyFile& eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber) {
	m_files = files;
	m_enemyFiles = eneFile;
	for (int i = 0; i < 6; i++) {
		m_monai[i] = monsterAI[i];
		m_ids[i] = monids[i];
	}
	m_dunNum = DunNumber;
}

void DungeonGame::StartTransition() {
	auto tra = NewGO<DungeonTransition>(0);
	tra->SetGameData(m_files, m_enemyFiles, m_monai, m_ids, m_dunNum);
	OutputDebugStringA("Created DungeonTransition Class\n");
}

void DungeonGame::StartNextDungeon() {
	m_dunNum += 1;
	IDungeonData().SetRound(0);
	StartTransition();
}

void DungeonGame::Relese() {
	IDungeonData().SetRound(0);
	DeleteGO(this);
}

void DungeonGame::PostRender() {
	if (!m_isInGame)
		return;
	m_font.Begin();
	wchar_t str[256];
	int round = IDungeonData().GetNumRound(m_dunNum);
	swprintf_s(str, L"Dungeon %d : Round %d/%d",m_dunNum + 1,m_round + 1, round + 1);
	m_font.Draw(str, {160.f , 344.f },CVector4::White,0.f,1.f);
	m_font.End();
}