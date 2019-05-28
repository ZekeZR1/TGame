#include "stdafx.h"
#include "GameCamera2D.h"

GameCamera2D::~GameCamera2D()
{
	delete camera2d;
}

bool GameCamera2D::Start()
{
	camera2d = new Camera;
	camera2d->SetTarget(CVector3::Zero());
	camera2d->SetPosition({ 0.0f, 0.0f, -10.0f });
	camera2d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	camera2d->SetNear(0.1f);
	camera2d->SetFar(1000.0f);
	camera2d->Update();
	return true;
}

void GameCamera2D::Update()
{
	camera2d->Update();
}
