#include "stdafx.h"
#include "../GameData.h"
#include "DungeonGame.h"
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
}