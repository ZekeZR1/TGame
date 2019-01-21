#include "stdafx.h"
#include "GameCamera3D.h"

bool GameCamera3D::Start()
{
	camera3d = new Camera;
	camera3d->SetTarget(CVector3::Zero());
	camera3d->SetPosition({ 0,0,-100 });
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->SetNear(0.1f);
	camera3d->SetFar(50000.0f);
	camera3d->Update();
	return true;
}

GameCamera3D::~GameCamera3D()
{
	delete camera3d;
}
