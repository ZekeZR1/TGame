#include "stdafx.h"
#include "../MonsterBox/MonsterBox.h"
#include "DungeonGame.h"
#include "../GameData.h"
#include "DungeonSelect.h"
#include "../GameCursor.h"
#include "DungeonData.h"
#include "DropEgg.h"
#include "../Fade/Fade.h"
#include <random>
#include "MonsterDrop.h"


MonsterDrop::MonsterDrop()
{
}


MonsterDrop::~MonsterDrop()
{
}


bool MonsterDrop::Start() {
	std::random_device rnd;
	auto drop = rnd() % 100;
	//if (drop >= 50) 
		//ToDungeonSelect();
	m_egg = NewGO<DropEgg>(0);
	camera3d->SetPosition({ 0.f,0.f,450.f });
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	camera3d->Update();
	InitUI();
	InitModels();
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	return true;
}

void MonsterDrop::OnDestroy() {
	DeleteGO(m_nextButtonSp);
	DeleteGO(m_notifySp);
	DeleteGO(m_monsterNameSp);
	DeleteGO(m_egg);
	DeleteGO(m_back);
	DeleteGO(m_cursor);
	DeleteGO(m_notifyFont);
}

void MonsterDrop::Update() {
	SceneTransition();
	Notifications();
#if _DEBUG
	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<MonsterDrop>(0);
	}
#endif
}



void MonsterDrop::ToDungeonSelect() {
	IDungeonData().SetRound(0);
	NewGO<DungeonSelect>(0);
	auto dGame = FindGO<DungeonGame>("DungeonGame");
	dGame->Relese();
	DeleteGO(this);
}

void MonsterDrop::SceneTransition() {
	m_nextButtonSp->SetCollisionTarget(m_cursor->GetCursor());
	if (m_nextButtonSp->isCollidingTarget()) {
		if (Mouse::isTrigger(enLeftClick)) {
			m_fadeFlag = true;
			m_fade->FadeOut();
		}
	}
	if (m_fade->isFadeStop() && m_fadeFlag) {
		ToDungeonSelect();
	}
}

void MonsterDrop::InitUI() {
	m_cursor = NewGO<GameCursor>(2);
	//m_monsterNameSp = NewGO<SpriteRender>(0);
	m_nextButtonSp = NewGO<SpriteRender>(0);
	m_nextButtonSp->Init(L"Assets/Sprite/button1.dds", 300.f, 100.f, true);
	m_nextButtonSp->SetMulCol({ 1.f,1.f,1.f,1.0f });
	m_nextButtonSp->SetPosition(m_nextButtonPos);

	m_notifyFont = NewGO<FontRender>(1);
	m_notifyFont->SetTextType(CFont::en_Japanese);
}

void MonsterDrop::InitModels() {
	m_back = NewGO<SkinModelRender>(0);
	m_back->Init(L"Assets/modelData/dropwall.cmo");
	m_back->SetPosition(m_backPosition);
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotationDeg(CVector3::AxisX(), 90.f);
	m_back->SetRotation(rot);
}


void MonsterDrop::Notifications() {
	if (m_isInited)
		return;
	auto name = m_egg->GetMonsterName();
	wchar_t q = L'?';
	if(wcschr(name, q) != nullptr)
		return;
	wchar_t notify[] = L"‚ðƒQƒbƒg‚µ‚Ü‚µ‚½";
	wcscat(name,notify);
	m_notifyFont->Init(name, { m_notifyLinePos.x - 250.f ,m_notifyLinePos.y + 20.f});
	m_notifySp = NewGO<SpriteRender>(0);
	m_notifySp->Init(L"Assets/Sprite/notifyLine.dds", 650.f, 50.f);
	m_notifySp->SetPosition(m_notifyLinePos);
	m_isInited = true;
}