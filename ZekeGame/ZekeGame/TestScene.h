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
	CEffect* m_efk = nullptr;
	SkinModelRender* m_meModel = nullptr;
	SkinModelRender* m_targetModel = nullptr;
	SkinModelRender* m_anotherMonster = nullptr;
	CVector3 m_targetPos = { 0,0,500 };
};
