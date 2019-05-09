#include "stdafx.h"
#include "../GameData.h"
#include "DungeonTransition.h"
#include "../StageSetup/StageSelect.h"
#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"
bool DungeonTransition::Start() {
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();

	Sound* bgm = NewGO<Sound>(0, "BGM");
	bgm->Init(L"Assets/sound/BGM/PerituneMaterial_OverWorld5_loop.wav",true);
	bgm->Play();

	m_back = NewGO<SkinModelRender>(0);
	m_back->Init(L"Assets/modelData/dungeonBack.cmo");
	CQuaternion m_rot = CQuaternion::Identity();
	m_rot.SetRotationDeg(CVector3::AxisY(), 180.f);
	//m_back->SetRotation(m_rot);
	m_back->SetScale({ 3.f,3.f,3.f });
	m_back->SetPosition(m_backPos);
	m_back->SetShadowCasterFlag(false);

	CVector3 pos = CVector3::Zero();
	pos.y -= 100.f;
	pos.z = -2000.f;
	for (int i = 0; i < m_numMonster; i++) {
		m_monsters.push_back(NewGO<SkinModelRender>(1));
		switch (m_ids[i]) {
		case enTest:
			m_monsters[i]->Init(L"Assets/modelData/tesEnemy3.cmo");//, m_animation, 1);
			break;
		case enUmataur:
			m_animClip[i][0].Load(L"Assets/modelData/uma/anim_uma_walk.tka");
			m_animClip[i][0].SetLoopFlag(true);
			m_monsters[i]->Init(L"Assets/modelData/uma.cmo", m_animClip[i], 1);
			m_monsters[i]->PlayAnimation(0);
			break;
		case enFairy:
			m_animClip[i][0].Load(L"Assets/modelData/fairy/hnd_idle.tka");
			m_animClip[i][0].SetLoopFlag(true);
			m_monsters[i]->Init(L"Assets/modelData/hnd.cmo", m_animClip[i], 1);
			m_monsters[i]->PlayAnimation(0);
			break;
		default:
			OutputDebugStringA("Trasan Anime < なんで？？？\n");
			break;

		}
		m_monsters[i]->SetPosition(pos);
		pos.x += 80.f;
	}
	m_camera = NewGO<DungeonTCamera>(0);
	OutputDebugStringA("Play Transition\n");
	return true;
}

void DungeonTransition::OnDestroy() {
	DeleteGO(m_back);
	DeleteGO(m_camera);
	for (auto model : m_monsters) {
		DeleteGO(model);
	}
	auto bgm = FindGO<Sound>("BGM");
	bgm->Stop();
}

void DungeonTransition::Update() {
	for (int i = 0; i < 3; i++) {
		auto pos = m_monsters[i]->GetPosition();
		pos.z += 5.f;
		m_monsters[i]->SetPosition(pos);
	}
	m_camera->SetTarget(m_monsters[1]->GetPosition());
	auto p = m_monsters[0]->GetPosition();
	if (p.z > -1100.f || g_pad[0].IsTrigger(enEscape)) {
		if (!m_isfade) {
			m_fade->FadeOut();
			//m_fade->SetMulCol(CVector4::White);
			m_isfade = true;
		}
	}
	char str[256];
	sprintf_s(str, "Pos %f\n", p.z);
	//OutputDebugString(str);
	if (m_isfade && m_fade->isFadeStop()) {
		auto select = NewGO<StageSelect>(0, "selectScene");
		select->SetDungeonGameData(m_files, m_enemyFiles, m_monai, m_ids, m_dunNum,m_aimode);
		DeleteGO(this);
	}
}

//
bool DungeonTCamera::Start() {
	camera3d->SetTarget(CVector3::Zero());
	camera3d->SetPosition(m_pos);
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->SetNear(0.1f);
	camera3d->SetFar(50000.0f);
	camera3d->SetViewAngle(CMath::DegToRad(60.f));
	camera3d->Update();
	return true;
}

void DungeonTCamera::OnDestroy() {
}

void DungeonTCamera::Update() {
	if (time2 >= 0.f) {
		time2 -= 0.004f;
	}
	double r = EASE::InQuad(1.f, 0.f, 1.f, time2);
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2 * r);
	qRot.Multiply(m_toCameraPos);
	CVector3 toCameraPosOld = m_toCameraPos;
	//
	if (time >= 0.f) {
		time -= 0.02f;
		xR = EASE::InQuad(1.f, 0.f, 1.f, time) * -1;
	}
	else {
		if (timee <= 1.f) {
			timee += 0.03f;
			xR = EASE::InQuad(1.f, 0.f, 1.f, timee);
		}
		else {
			if (time4 > 0.f) {
				time4 -= 0.03f;
				xR = EASE::InQuad(1.f, 0.f, 1.f, time4);
			}
			else {
				xR = 0.f;
			}
		}
	}
	//
	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX,  xR );
	qRot.Multiply(m_toCameraPos);
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	CVector3 pos = m_target + m_toCameraPos;
	CQuaternion m_rot; 
	m_target.y += 100.f;
	camera3d->SetTarget(m_target);
	camera3d->SetPosition(pos);
	camera3d->Update();
}


void DungeonTransition::SetGameData(PyFile& files, PyFile& eneFile, int monsterAI[6], MonsterID monids[6], int DunNumber, int aimode[6]) {
	m_files = files;
	m_enemyFiles = eneFile;
	for (int i = 0; i < 6; i++) {
		m_monai[i] = monsterAI[i];
		m_ids[i] = monids[i];
		m_aimode[i] = aimode[i];
	}
	m_dunNum = DunNumber;
}