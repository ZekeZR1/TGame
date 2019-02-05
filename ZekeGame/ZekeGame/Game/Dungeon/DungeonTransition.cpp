#include "stdafx.h"
#include "../GameData.h"
#include "DungeonTransition.h"
#include "../StageSetup/StageSelect.h"

bool DungeonTransition::Start() {
	m_back = NewGO<SkinModelRender>(0);
	m_back->Init(L"Assets/modelData/dungeonBack.cmo");
	CQuaternion m_rot = CQuaternion::Identity();
	m_rot.SetRotationDeg(CVector3::AxisY(), 180.f);
	//m_back->SetRotation(m_rot);
	m_back->SetScale({ 3.f,3.f,3.f });
	m_back->SetPosition(m_backPos);

	CVector3 pos = CVector3::Zero();
	m_animation[0].Load(L"Assets/modelData/uma/anim_uma_walk.tka");
	m_animation[0].SetLoopFlag(true);
	pos.y -= 100.f;
	pos.z = -2000.f;
	for (int i = 0; i < m_numMonster; i++) {
		m_monsters.push_back(NewGO<SkinModelRender>(1));
		switch (m_ids[i]) {
		case enTest:
			m_monsters[i]->Init(L"Assets/modelData/tesEnemy3.cmo");//, m_animation, 1);
			break;
		case enUmataur:
			m_monsters[i]->Init(L"Assets/modelData/uma.cmo");//, m_animation, 1);
			break;
		case enFairy:
			m_monsters[i]->Init(L"Assets/modelData/hnd.cmo");// , m_animation, 1);
			break;
		default:
			break;
		}
		m_monsters[i]->SetPosition(pos);
		//m_monsters[i]->PlayAnimation(0);
		pos.x += 80.f;
	}
	m_camera = NewGO<DungeonTCamera>(0);

	return true;
}

void DungeonTransition::OnDestroy() {
	DeleteGO(m_back);
	DeleteGO(m_camera);
	for (auto model : m_monsters) {
		DeleteGO(model);
	}
}

void DungeonTransition::Update() {
	for (int i = 0; i < 3; i++) {
		auto pos = m_monsters[i]->GetPosition();
		pos.z += 5.f;
		m_monsters[i]->SetPosition(pos);
	}
	m_camera->SetTarget(m_monsters[1]->GetPosition());
	auto p = m_monsters[0]->GetPosition();
	if (p.z > 0.f) {
		auto select = NewGO<StageSelect>(0, "selectScene");
		select->SetDungeonGameData(m_files, m_enemyFiles, m_monai, m_ids, m_dunNum);
		DeleteGO(this);
	}
}

//
bool DungeonTCamera::Start() {
	//camera3d = new Camera;
	camera3d->SetTarget(CVector3::Zero());
	camera3d->SetPosition(m_pos);
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->SetNear(0.1f);
	camera3d->SetFar(50000.0f);
	camera3d->Update();
	return true;
}

void DungeonTCamera::OnDestroy() {
	//delete camera3d;
}

void DungeonTCamera::Update() {
	 float r = 1.f;
	 count++;
	 if (count >= 90 ) {
		 r = 0.f;
	 }
	//Y������̉�]
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2 * r);
	qRot.Multiply(m_toCameraPos);
	CVector3 toCameraPosOld = m_toCameraPos;
	//
	if (count <= 90 / 2 ) {
		xR = 0.7f;
	}
	else if(count <= 90){
		xR = -0.8f;
	}
	else {
		xR = 0.f;
	}
	//
	//X������̉�]�B
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX,  -xR);
	qRot.Multiply(m_toCameraPos);
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	CVector3 pos = m_target + m_toCameraPos;
	CQuaternion m_rot; 
	camera3d->SetTarget(m_target);
	camera3d->SetPosition(pos);
	camera3d->Update();
}


void DungeonTransition::SetGameData(PyFile& files, PyFile& eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber) {
	m_files = files;
	m_enemyFiles = eneFile;
	for (int i = 0; i < 6; i++) {
		m_monai[i] = monsterAI[i];
		m_ids[i] = monids[i];
	}
	m_dunNum = DunNumber;
}