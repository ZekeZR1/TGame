#pragma once
#include"Engine/character/CharacterController.h"

class GameCamera;
class GameCamera2D;
class GameCursor;
class TestScene : public GameObject
{
public:
	TestScene();
	~TestScene();
	bool Start();
	void Update();
	void Nyan();
private:
	//Hashtable hamu[3];
};
