#include "stdafx.h"
#include <fstream>
#include "GameCamera.h"
#include "Game/GameData.h"
#include "Game/Dungeon/DungeonData.h"
#include "Game/GameCamera2D.h"
#include "Game/GameCursor.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "Engine\sound\CSound.h"
#include"Engine/physics/PhysicsStaticObject.h"
#include"Engine/character/CharacterController.h"
#include "Game/MonsterBox/MonsterBox.h"

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

//TODO : alpha, shadow
bool TestScene::Start() {
	Nyan();
	return true;
}


void TestScene::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		Nyan();
	}
}


void TestScene::Nyan() {
	using namespace std;
	char cd[255] = { '\0' };
	GetCurrentDirectoryA(255, cd);
	std::string path = "\\Assets\\VisualAI\\";
	path += "002.va";
	char* cstr = new char[path.size() + 1];
	std::char_traits<char>::copy(cstr, path.c_str(), path.size() + 1);
	strcat(cd, cstr);
	delete[] cstr;

	int datas[1024];
	ifstream ifs(cd, ios::in | ios::binary);
	if (!ifs) return;
	int ch;
	int index = 0;
	for (int i = 0; i < 1024; i++) {
		int x;
		ifs.read((char*)&x,sizeof(int));
		datas[i] = x;
	}
	ifs.close();
	//write
	std::wstring VaFileName = L"NetworkEnemyAIs/";
	//VaFileName += std::to_wstring(number + 1);
	VaFileName += L"1enemy.va";
	const wchar_t* utf8fname = VaFileName.c_str();
	ofstream ost("NetworkEnemyAIs/1enemy.va", ios::out | ios::binary);
	for (int i = 0; i < 1024; i++) {
		ost.write((char*)&datas[i],sizeof(int));
	}
	ost.close();
}