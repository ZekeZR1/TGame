#include "stdafx.h"
#include "ModeSelectBack.h"

ModeSelectBack::ModeSelectBack()
{
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	camera3d->SetTarget(CVector3::Zero());
	camera3d->SetPosition({ 0,0,-800 });
	camera3d->Update();

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisY(), -180);
	/*m_back = NewGO<SkinModelRender>(0, "sr");
	m_back->Init(L"Assets/modelData/mdsel_None.cmo",nullptr,0,enFbxUpAxisZ,"PSMainStage");
	
	m_back->SetRotation(rot);
	m_back->SetScale(CVector3::One() * 100);
	m_back->SetPosition({ 0,0,-500 });*/

	m_backS = NewGO<SpriteRender>(0, "sp");
	m_backS->Init(L"Assets/sprite/modesel_back_aiedit.dds", 1280, 720);
	m_backS->SetPosition({ 0,0,100 });
	m_backS->ChangeCameraProjMatrix(Camera::enUpdateProjMatrixFunc_Perspective);
	//m_backS->SetRotation(rot);
	

	m_effect = NewGO<CEffect>(0, "ef");
	m_effect->Play(L"Assets/effect/fireFlower.efk");
	m_effect->SetScale(CVector3::One()*2);
	m_effect->SetPosition({ 0,-360,0 });
}

void ModeSelectBack::OnDestroy()
{
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->Update();

	DeleteGO(m_back);
	m_effect->Stop();
	DeleteGO(m_effect);
}