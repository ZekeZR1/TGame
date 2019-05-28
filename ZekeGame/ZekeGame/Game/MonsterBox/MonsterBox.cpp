#include "stdafx.h"
#include "MonsterBox.h"
#include "../GameData.h"
#include <memory>
#include <fstream>
#include <cmath>


bool MonsterBox::isGot(MonsterID id) {
	LoadMyBox();
	if (m_monsters[id])
		return true;
	else
		return false;
	//if(m_monsters % id == 0)
	/*int flagnum[enNumMonster];
	int mons = m_monsters;
	for (int i = 0; i < enNumMonster; i++) {
		flagnum[i] = mons % 10;
		mons /= 10;
	}
	if (flagnum[id] != 0)
		return true;
	return false;*/
}

void MonsterBox::GetMonster(MonsterID id) {
	using namespace std;
	LoadMyBox();
	m_monsters[id] = 1;
	ofstream fout;
	fout.open("Assets/saveData/monsterbox.mbx", ios::out or ios::binary);
	for (int i = 0; i < enNumMonster; i++) {
		fout.write((char*)&m_monsters[i], sizeof(int));
	}
	fout.close();
	/*int x =  std::pow(10, static_cast<int>(id));
	int flagnum[enNumMonster];
	int mons = m_monsters;
	for (int i = 0; i < enNumMonster; i++) {
		flagnum[i] = mons % 10;
		mons /= 10;
	}
	if (flagnum[id] == 0)
		m_monsters += x;
	WriteFile(m_monsters);*/
}


void MonsterBox::initFile() {
	using namespace std;
	ofstream fout;
	fout.open("Assets/saveData/monsterbox.mbx", ios::out | ios::binary | ios::trunc);
	int n = 0;
	for (int i = 0; i < enNumMonster; i++) {
		fout.write((char*)&n, sizeof(int));
		//fout << 0;
	}
	fout.close();
}


void MonsterBox::LoadMyBox() {
	using namespace std;
	ifstream fin("Assets/saveData/monsterbox.mbx", ios::in | ios::binary);
	if (!fin) {
		OutputDebugStringA("monsterbox.mbx‚ÌƒI[ƒvƒ“‚ÉŽ¸”s‚µ‚Ü‚µ‚½\n");
		for (int i = 0; i < enNumMonster; i++) {
			m_monsters[i] = 0;
		}
		initFile();
		return;
	}
	for (int i = 0; i < enNumMonster; i++) {
		fin.read((char *)&m_monsters[i], sizeof(int));
	}
	fin.close();
}