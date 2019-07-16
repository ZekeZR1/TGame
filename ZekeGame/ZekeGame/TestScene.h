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
	SkinModelRender* m_model = nullptr;
	SkinModelRender* m_floor = nullptr;
	SkinModelRender* m_monster = nullptr;
	AnimationClip m_anim[6];		//anime
	CVector3 camerapos;
	CQuaternion m_rot = CQuaternion::Identity();
};
