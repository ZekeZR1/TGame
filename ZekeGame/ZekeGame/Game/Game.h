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
	bool Start() override;
	void Update() override;
	void Render() override;
	void PostRender() override;

private:
	SkinModelRender* m_model;
	SpriteRender* m_sprite;
	GameCamera* camera = nullptr;
	StageSetup* ss;

	//AnimationTest
	//SkinModelRender*  m_ringo;
	SkinModel m_ringo;
	AnimationClip m_animationClips[2];
	Animation m_animation;
	//
};

