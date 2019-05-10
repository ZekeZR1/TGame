#pragma once
#include"Engine/character/CharacterController.h"


class GameCamera;
class GameCamera2D;
class GameCursor;

using namespace ExitGames::Common;
using namespace ExitGames::LoadBalancing;

class TestScene : public GameObject
{
public:
	TestScene();
	~TestScene();
	bool Start();
	void Update();
	void Nyan();
private:
	Hashtable h[3];
};
