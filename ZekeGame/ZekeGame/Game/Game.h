#pragma once
//#include "GameCamera.h"

#include "StageSetup/StageSetup.h"

class GameCamera;
class TestListener;

class Game : public GameObject
{
public:
	Game();
	~Game();
	void GamePVPmodeInit(std::vector<std::string> files, int monsterAI[6]);
	bool Start() override;
	void Update() override;
	void Render() override;
	void PostRender() override;

private:
	SkinModelRender* m_model;
	SpriteRender* m_sprite;
	GameCamera* camera = nullptr;
	StageSetup* ss;
};

