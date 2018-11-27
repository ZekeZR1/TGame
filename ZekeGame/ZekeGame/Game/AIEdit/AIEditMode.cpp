#include "stdafx.h"
#include "AIEditMode.h"

#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"

AIEditMode::~AIEditMode()
{
	//メモリ開放はしっかりしよう！！

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
}
