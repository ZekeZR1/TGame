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
	ifstream ifs;
	JString data;
	ifs.open(cd, ios::in | ios::binary);
	if(!ifs)
		OutputDebugString("1enemy.va open failed\n");
	ifs.seekg(0,fstream::end);
	UINT endpos = ifs.tellg();
	ifs.seekg(0, fstream::beg);
	while (ifs.tellg() != endpos) {
		byte x;
		ifs.read((char*)& x, 1);
		char ss[256];
		sprintf_s(ss, "%02x", x);
		data += ss;
	}
	/*for (int i = 0; i < 1024; i++) {
		byte x;
		ifs.read((char*)&x, 1);
		char ss[256];
		sprintf_s(ss, "%02x", x);
		data += ss;
		if (ifs.eof())
			break;
	}*/
	ofstream ofs;
	ofs.open("NetworkEnemyAIs/1enemy.va", ios::out | ios::binary);
	if (!ofs) {
		OutputDebugString("1enemy.va open failed\n");
	}
	for (int i = 0; i < data.capacity(); i+=2) {
		string nyan = "0x";
		nyan += data[i];
		nyan += data[i + 1];
		byte x = atof(nyan.c_str());
		ofs.write((char*)& x, 1);
	}
}