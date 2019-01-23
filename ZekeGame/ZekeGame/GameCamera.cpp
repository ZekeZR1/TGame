#include "stdafx.h"
#include "GameCamera.h"
#include "Game/GameData.h"

GameCamera::GameCamera()
{
	
	/*camera2d = new Camera;
	camera2d->SetTarget(CVector3::Zero());
	camera2d->SetPosition({ 0.0f, 0.0f, -10.0f });
	camera2d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);	
	camera2d->SetNear(0.1f);
	camera2d->SetFar(1000.0f);
	camera2d->Update();*/
	
	/*camera3d = new Camera;
	camera3d->SetTarget(m_target);
	camera3d->SetPosition(m_pos);
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->SetNear(0.1f);
	camera3d->SetFar(50000.0f);
	camera3d->Update();*/
}


GameCamera::~GameCamera()
{
	//delete camera2d;
	//delete camera3d;
}

/*
	毎フレーム呼ばれるゲームカメラの更新
*/
void GameCamera::Update() {
	//camera2d->Update();

	if (g_pad[0].IsTrigger(enButtonUp))
	{
		m_inm++;
		if (m_inm >= 6)
		{
			m_inm = -1;
		}
	}
	else if (g_pad[0].IsTrigger(enButtonDown))
	{
		m_inm--;
		if (m_inm < -1)
		{
			m_inm = 5;
		}
	}

	if (m_inm == -1)
	{
		normal();
	}
	else
	{
		focus();
	}
	
	camera3d->Update();
}

void GameCamera::normal()
{
	SkinModelRender* i_model = nullptr;
	i_model = FindGO<SkinModelRender>("model");
	//m_target = i_model->GetPosition();
	m_target = CVector3::Zero();


	float x = g_pad[0].GetRStickXF();
	float y = g_pad[0].GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
	qRot.Multiply(m_toCameraPos);


	CVector3 toCameraPosOld = m_toCameraPos;

	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(m_toCameraPos);
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	CVector3 pos = m_target + m_toCameraPos;

	camera3d->SetTarget(m_target);
	camera3d->SetPosition(pos);
}

void GameCamera::focus()
{
	if (g_mons[m_inm] == nullptr)
	{
		m_inm--;
	}
	CQuaternion rot = g_mons[m_inm]->GetRotation();
	CVector3 vec = CVector3::Front();
	rot.Multiply(vec);

	CVector3 pos = g_mons[m_inm]->Getpos();
	CVector3 ms = g_mons[m_inm]->Getspeed();
	
	ms.Normalize();
	CVector3 cpo = pos + vec * -250;
	cpo.y += 150;

	CVector3 cta = pos + vec * 250;
	camera3d->SetTarget(cta);
	camera3d->SetPosition(cpo);

}
