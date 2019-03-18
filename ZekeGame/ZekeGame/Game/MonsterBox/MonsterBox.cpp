#include "stdafx.h"
#include "MonsterBox.h"
#include "../GameData.h"
#include <memory>
#include <fstream>
#include <cmath>

bool MonsterBox::isGot(MonsterID id) {
	CheckMonsterData();
	int x = std::pow(10, static_cast<int>(id));
	int nums[enNumMonster];
	int mons = m_monsters;
	for (int i = 0; i < enNumMonster; i++) {
		nums[i] = mons % 10;
		mons /= 10;
	}
	char str[256];
	sprintf_s(str, "monster num %d\n", m_monsters);
	OutputDebugStringA(str);
	if (nums[id] != 0) {
		return true;
	}
	else {
		return false;
	}
}

void MonsterBox::GetMonster(MonsterID id) {
	int x =  std::pow(10, static_cast<int>(id));
	int nums[enNumMonster];
	int mons = m_monsters;
	for (int i = 0; i < enNumMonster; i++) {
		nums[i] = mons % 10;
		mons /= 10;
	}
	if (nums[id] == 0)
		m_monsters += x;
	char str[256];
	WriteFile(m_monsters);
	sprintf_s(str, "monster num %d\n", m_monsters);
	OutputDebugStringA(str);
}

void MonsterBox::CheckMonsterData() {
	using namespace std;
	char outfile[] = "monsterbox.txt";
	ifstream fin(outfile, ios::in | ios::binary);
	if (!fin) {
		OutputDebugStringA("monsterbox.txt‚ÌƒI[ƒvƒ“‚ÉŽ¸”s‚µ‚Ü‚µ‚½\n");
		WriteFile(0);
		return;
	}
	fin.read((char *)&m_monsters, sizeof(int));
	fin.close();
}

void MonsterBox::WriteFile(int n) {
	using namespace std;
	 m_monsters = n;
	ofstream fout;
	OutputDebugStringA("writing monsterbox file\n");
	fout.open("monsterbox.txt", ios::out | ios::binary | ios::trunc);
	fout.write((char*)&m_monsters, sizeof(int));
	fout.close();
}