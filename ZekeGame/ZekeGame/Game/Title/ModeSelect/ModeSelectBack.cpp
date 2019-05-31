#include "stdafx.h"
#include "ModeSelectBack.h"

ModeSelectBack::ModeSelectBack()
{
	//camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
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

void ModeSelectBack::Update()
{
	if (m_isfirst)
	{
		switch (m_mode)
		{
		case endundeon:
			break;
		case enpvp:
			break;
		case ennetpvp:
			break;
		case enAIedit:
			break;
		}
	}
}

void ModeSelectBack::Dungeon()
{
	SpriteRender* sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_dun.dds", 1280, 673);

	m_sprits.push_back(sp);
	
	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_eye.dds", 303, 193);
	m_sprits.push_back(sp);

	m_mode = endundeon;
}

void ModeSelectBack::PVP()
{

	SpriteRender* sp;
	for (int i = 0; i < 3; i++)
	{
		sp = NewGO<SpriteRender>(0, "sp");
		sp->Init(L"Assets/sprite/modesel_p.dds", 339, 243);
		m_sprits.push_back(sp);
	}

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisZ(), 180);
	for (int i = 0; i < 3; i++)
	{
		sp = NewGO<SpriteRender>(0, "sp");
		sp->Init(L"Assets/sprite/modesel_p.dds", 339, 243);
		sp->SetRotation(rot);
		m_sprits.push_back(sp);
	}

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_blackF.dds", 726, 116);
	m_sprits.push_back(sp);

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_VS.dds", 708, 367);
	m_sprits.push_back(sp);

	m_mode = enpvp;
}

void ModeSelectBack::NetPVP()
{
	SpriteRender* sp;
	for (int i = 0; i < 3; i++)
	{
		sp = NewGO<SpriteRender>(0, "sp");
		sp->Init(L"Assets/sprite/modesel_p.dds", 339, 243);
		m_sprits.push_back(sp);
	}

	CQuaternion rot;
	rot.SetRotationDeg(CVector3::AxisZ(), 180);
	for (int i = 0; i < 3; i++)
	{
		sp = NewGO<SpriteRender>(0, "sp");
		sp->Init(L"Assets/sprite/modesel_p.dds", 339, 243);
		sp->SetRotation(rot);
		m_sprits.push_back(sp);
	}

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_earth.dds", 304, 295);
	m_sprits.push_back(sp);

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_blackF.dds", 726.f*0.7f, 116.f * 0.7f);
	m_sprits.push_back(sp);

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_VS.dds", 708.f * 0.7f, 367.f * 0.7f);
	m_sprits.push_back(sp);

	m_mode = ennetpvp;
}

void ModeSelectBack::AIedit()
{
	SpriteRender* sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_txt.dds", 440, 236);
	m_sprits.push_back(sp);

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/gear.dds", 400, 400);
	m_sprits.push_back(sp);

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/gear.dds", 400, 400);
	m_sprits.push_back(sp);

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/modesel_brain.dds", 571, 456);
	m_sprits.push_back(sp);

	sp = NewGO<SpriteRender>(0, "sp");
	sp->Init(L"Assets/sprite/gear.dds", 400, 400);
	m_sprits.push_back(sp);

	m_mode = enAIedit;
}

void ModeSelectBack::delSprits()
{
	for (auto sp : m_sprits)
	{
		DeleteGO(sp);
	}
	m_sprits.clear();
	m_sprits.shrink_to_fit();
}

void ModeSelectBack::moveDungeon()
{
}

void ModeSelectBack::movePVP()
{
}

void ModeSelectBack::moveNETPVP()
{
}

void ModeSelectBack::moveAIedit()
{
}
