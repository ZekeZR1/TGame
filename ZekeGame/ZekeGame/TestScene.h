#pragma once
#include"Engine/character/CharacterController.h"


class GameCamera;
class GameCamera2D;
class GameCursor;

class GameCursor;

class TestScene : public GameObject
{
public:
	bool Start() override;
	void OnDestroy() override;
	void Update() override;
private:
};
