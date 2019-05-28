#include "stdafx.h"
#include "../GameData.h"
#include "DungeonData.h"

void DungeonData::SetGameData(PyFile files, PyFile eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber) {
	m_files = files;
	m_enemyFiles = eneFile;
	for (int i = 0; i < 6; i++) {
		m_monai[i] = monsterAI[i];
		m_ids[i] = monids[i];
	}
	m_dunNum = DunNumber;
}

bool DungeonData::isFinalRound(int DunNum) {
	if (GetRound() == m_rounds[DunNum])
		return true;
	else
		return false;
}

const int DungeonData::GetNumRound(int dungeon) {
	return m_rounds[dungeon];
}