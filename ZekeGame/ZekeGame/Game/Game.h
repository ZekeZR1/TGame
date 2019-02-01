#pragma once
//#include "GameCamera.h"

#include "StageSetup/StageSetup.h"

enum MonsterID;
class GameCamera;
class TestListener;
class GameMenu;
struct Pyinit;

class Game : public GameObject
{
public:
	void GamePVPmodeInit(std::vector<std::string> files, int monsterAI[6], MonsterID MonsterID[6]);
	bool Start() override;
	void OnDestroy() override;
	void Update() override;

	enum Mode
	{
		enLocalPVP,
		enRandomPVP,
		enDungeon
	};

	void LocalPVP()
	{
		m_playMode = enLocalPVP;
	}

	void DungeonMode(int number)
	{
		m_playMode = enDungeon;
		m_dunNum = number;
	}


private:
	Pyinit* m_pi;
	SkinModelRender* m_model;
	SpriteRender* m_sprite;
	GameCamera* camera = nullptr;
	StageSetup* ss;
	int m_dunNum = -1;
	GameMenu* m_menu = nullptr;

	Mode m_playMode = enLocalPVP;

	bool m_END = false;
	bool m_isOnlineGame = false;
};

