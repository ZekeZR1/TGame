#include "stdafx.h"
#include "ResultCamera.h"

ResultCamera::~ResultCamera()
{
	delete camera3d;
}

bool ResultCamera::Start()
{
	camera3d = new Camera;
	camera3d->SetTarget(m_tar);
	camera3d->SetPosition(m_pos);
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->SetNear(0.1f);
	camera3d->SetFar(50000.0f);
	camera3d->Update();
	return true;
}

void ResultCamera::Update()
{
	camera3d->SetPosition(m_pos);
	camera3d->SetTarget(m_tar);
	camera3d->Update();
}
