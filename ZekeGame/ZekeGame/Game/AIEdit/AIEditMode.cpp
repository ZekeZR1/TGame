#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
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

	//!!!--RETURN TRUE--!!!
	return true;
	//!!!--RETURN TRUE--!!!
}

void AIEditMode::Update()
{

	if (Mouse::isTrigger(enRightClick)) {
		m_aieditnode = NewGO<AIEditNode>(0, "window");
	}

}
