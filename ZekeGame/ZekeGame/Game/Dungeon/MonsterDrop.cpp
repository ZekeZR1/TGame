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
	//std::random_device rnd;
	//auto drop = rnd() % 100;
	//if (drop >= 50 - m_stage) {
	//	ToDungeonSelect();
	//	return true;
	//}
	if (m_stage == 7) {
		ToDungeonSelect();
		return true;
	}
	m_egg = NewGO<DropEgg>(0);
	auto id = static_cast<MonsterID>(m_stage + 2);
	m_egg->SetDropMonster(id);
	InitCamera();
	InitUI();
	InitModels();

	auto bgm = FindGO<Sound>("BGM");
	if (bgm != nullptr)
	{
		bgm->Stop();
	}
	m_BGM = NewGO<Sound>(0, "BGM");
	m_BGM->Init(L"Assets/sound/dungeon/mond.wav", true);
	m_BGM->Play();

	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	return true;
}

void MonsterDrop::OnDestroy() {
	DeleteGO(m_notifySp);
	DeleteGO(m_monsterNameSp);
	DeleteGO(m_egg);
	DeleteGO(m_BGM);
	DeleteGO(m_notifyFont);
	DeleteGO(m_nextfont);
	DeleteGO(m_back);
	auto ef = FindGO<CEffect>("DRB");
	if(ef!=nullptr)
		ef->Stop();
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
	if (Mouse::isTrigger(enLeftClick) and m_isInited) {
		m_fadeFlag = true;
		m_fade->FadeOut();
		auto se = NewGO<Sound>(0);
		se->Init(L"Assets/sound/se/button.wav", false);
		se->Play();
	}
	if (m_fade->isFadeStop() && m_fadeFlag) {
		ToDungeonSelect();
	}
}

void MonsterDrop::InitUI() {
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
	auto namesize = sizeof(name) / sizeof(wchar_t);
	m_fontFix = namesize * 12;
	wchar_t q = L'?';
	if(wcschr(name, q) != nullptr)
		return;
	wchar_t notify[] = L"をゲットしました";
	wcscat(name,notify);
	m_notifyFont->Init(name, { m_notifyLinePos.x - 250.f - m_fontFix ,m_notifyLinePos.y + 20.f});
	m_notifyFont->DrawShadow();
	m_notifySp = NewGO<SpriteRender>(0);
	m_notifySp->Init(L"Assets/Sprite/notifyLine.dds", 750.f, 80.f);
	m_notifySp->SetPosition(m_notifyLinePos);

	m_nextfont = NewGO<FontRender>(5, "fr");
	m_nextfont->SetTextType(CFont::en_Japanese);
	m_nextfont->Init(L"クリックしてください", { -600,-300 }, 0, { 1,1,1,1 }, 1, { 0,0 });
	m_nextfont->DrawShadow();

	m_back->Init(L"Assets/modelData/gorgeousWall.cmo");

	m_isInited = true;
}

void MonsterDrop::InitCamera() {
	camera3d->SetTarget(CVector3::Zero());
	camera3d->SetNear(0.1f);
	camera3d->SetFar(50000.0f);
	camera3d->SetPosition({ 0.f,0.f,450.f });
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	camera3d->Update();

	camera2d->SetTarget(CVector3::Zero());
	camera2d->SetPosition({ 0.0f, 0.0f, -10.0f });
	camera2d->SetNear(0.1f);
	camera2d->SetFar(1000.0f);
	camera2d->Update();
}