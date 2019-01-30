#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include"AIEditNodeClick.h"
#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"

AIEditMode::~AIEditMode()
{
	//ÉÅÉÇÉääJï˙ÇÕÇµÇ¡Ç©ÇËÇµÇÊÇ§ÅIÅI

	// CAMERA IS DEAD.
	delete m_camera;

	//CURSOR IS DEAD.
	DeleteGO(m_cursor);
}

bool AIEditMode::Start()
{
	// THIS IS CAMERA.
	m_camera = new GameCamera;

	m_cursor = NewGO<GameCursor>(0, "cursor");

	m_spriteRender = NewGO<SpriteRender>(0, "win");
	m_spriteRender->Init(L"Assets/sprite/haik.dds", 1280,720);
	m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "firstbutton");

	//!!!--RETURN TRUE--!!!
	return true;
	//!!!--RETURN TRUE--!!!
}

void AIEditMode::Update()
{

}
