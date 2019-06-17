#include "stdafx.h"
#include <memory>
#include <fstream>
#include "DungeonData.h"
#include "../Title/ModeSelect.h"
#include "../GameCursor.h"
#include "../StageSetup/StageSetup.h"
#include "DungeonAISelect.h"
#include "DungeonSelect.h"
#include "../Fade/Fade.h"

#include "../ReturnButton/ReturnButton.h"

bool DungeonSelect::Start() {
	m_cur = NewGO<GameCursor>(3, "cur");
	InitSideButtons();
	CheckDungeonClearState();
	InitDungeonButtons();
	InitBackButton();
	auto bgm = FindGO<Sound>("BGM");
	if (bgm == nullptr)
	{
		bgm = NewGO<Sound>(0, "BGM");
		bgm->Init(L"Assets/sound/BGM/PerituneMaterial_Strategy5_loop.wav", true);
		bgm->Play();
	}
	m_wallpaper = NewGO<SpriteRender>(0);
	m_wallpaper->Init(L"Assets/Sprite/dungeonSelectWallpaper.dds", 1280.f, 720.f);
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	return true;
}

void DungeonSelect::OnDestroy() {
	DeleteGO(m_cur);
	for (auto sp : m_sps) {
		DeleteGO(sp);
	}
	for (auto font : m_fonts) {
		DeleteGO(font);
	}
	if (m_nextSp != nullptr) {
		DeleteGO(m_nextSp);
	}
	//DeleteGO(m_backSp);
	DeleteGO(m_returnButton);
	
	DeleteGO(m_backTx);
	DeleteGO(m_leftSp);
	DeleteGO(m_rightSp);
	DeleteGO(m_wallpaper);
	m_dungeonButton.clear();
}

void DungeonSelect::Update() {
	DungeonSelectClick();
	NextSpAnimation();
	PositionUpdate();
	StartDungeon();
	BackToMenu();
}

void DungeonSelect::CheckDungeonClearState() {
	{
		using namespace std;
		char outfile[] = "Assets/saveData/clearstate.dd";
		ifstream fin(outfile, ios::in | ios::binary);
		if (!fin) {
			OutputDebugStringA("clearstate.ddのオープンに失敗しました");
			ofstream fout;
			fout.open(outfile, ios::out | ios::binary | ios::trunc);
			int n = -1;
			fout.write((char*)&n, sizeof(int));
			fout.close();
			return;
		}
		int clearedDungeon = -1;
		fin.read((char *)&clearedDungeon, sizeof(int));
		fin.close();
		if (clearedDungeon < 0 || clearedDungeon > 8) {
			clearedDungeon = -1;
			ofstream fout;
			fout.open(outfile, ios::out | ios::binary | ios::trunc);
			fout.write((char*)&clearedDungeon, sizeof(int));
			fout.close();
			OutputDebugStringA("ダンジョンのクリアデータが謎い\n");
			char message[256];
			sprintf_s(message, "%d\n", clearedDungeon);
			OutputDebugStringA(message);
		}
		m_clearedDunNum = clearedDungeon;
	}
}

void DungeonSelect::InitDungeonButtons() {
	if (m_clearedDunNum != m_numDungeon - 1) {
		m_nextSp = NewGO<SpriteRender>(2);
		m_nextSp->Init(L"Assets/Sprite/nextDungeon.dds", 90.f, 30.f);
	}
	CVector3  pos = CVector3::Zero();
	for (int i = 0; i < m_numDungeon; i++) {
		//init sprite
		m_sps.push_back(NewGO<SpriteRender>(1, "sp"));
		m_sps[i]->Init(L"Assets/Sprite/dun_stage0.dds", SPRITE_W, SPRITE_H, true);
		m_sps[i]->SetPosition(pos);
		//init text
		m_fonts.push_back(NewGO<FontRender>(2, "font"));
		m_fonts[i]->SetTextType(CFont::TextType::en_Japanese);
		wchar_t dungeon[256];
		swprintf_s(dungeon, L"ダンジョン%d", i + 1);
		CVector4 fontCol;
		if (i == m_clearedDunNum + 1) {
			CVector3 m_nextDunPos = pos;
			m_nextDunPos.x += 200.f;
			m_nextDunPos.y += 250.f;
			m_nextSp->SetPosition(m_nextDunPos);
		}
		if (i > m_clearedDunNum + 1) {
			fontCol = m_notYetClearCol;
		}
		else {
			fontCol = m_ClearCol;
		}
		m_fonts[i]->Init(dungeon, { pos.x + m_toFixMisalignment.x, pos.y + m_toFixMisalignment.y }, 0.f, fontCol, 1.f, m_fPivot);
		//set next position
		pos.x += m_spaceToNextSprite;
		//map
		m_dungeonButton[m_sps[i]] = i;
	}
}

void DungeonSelect::InitSideButtons() {
	{
		CVector3 pos = { 400.f,0.f,0.f };
		m_leftSp = NewGO<SpriteRender>(3);
		m_leftSp->Init(L"Assets/Sprite/leftButton.dds", 50.f, 100.f, true);
		m_leftSp->SetPosition(pos * -1);
		m_rightSp = NewGO<SpriteRender>(3);
		m_rightSp->Init(L"Assets/Sprite/rightButton.dds", 50.f, 100.f, true);
		m_rightSp->SetPosition(pos);
	}
}

void DungeonSelect::InitBackButton() {
	m_returnButton = NewGO<ReturnButton>(0, "rb");
	m_returnButton->init(this, "modesel", m_cur);

	/*m_backSp = NewGO<SpriteRender>(1);
	m_backSp->Init(L"Assets/Sprite/button1.dds", 180.f, 60.f, true);
	CVector3 sPos = { -500.f, -270.f, 0.f };
	m_backSp->SetPosition(sPos);
	m_backTx = NewGO<FontRender>(1);
	m_backTx->SetTextType(CFont::TextType::en_Japanese);
	CVector2 tPos;
	tPos.x = sPos.x;
	tPos.x += -45;
	tPos.y = sPos.y;
	tPos.y += 16.f;
	m_backTx->Init(L"戻る", tPos, 0.f, CVector4::White, 1.f, { 0.f,0.f });*/
}

void DungeonSelect::PositionUpdate() {
	for (auto button : m_sps) {
		auto pos = button->GetPosition();
		button->SetPosition(pos += addPos);
	}
	for (auto font : m_fonts) {
		CVector2 pos = font->GetPosition();
		pos.x += addPos.x;
		font->SetPosition(pos);
	}

	if (m_nextSp != nullptr) {
		CVector3 pos = m_nextSp->GetPosition();
		m_nextSp->SetPosition(pos + addPos);
	}
}

void DungeonSelect::NextSpAnimation() {
	if (m_nextSp == nullptr)
		return;

	static unsigned int count = 0;
	CVector3 scale = CVector3::One();

	if (count >= UINT_MAX) 
		count = 0;
	
	double sca = 1.f;
	sca = 1.5f + sin(M_PI * 2 / 30 * count) * 0.05f;
	m_nextSp->SetScale(scale * sca);
	count++;
}

void DungeonSelect::DungeonSelectClick() {
	static bool left = false, right = false;
	static double change = 177.f;
	const double duration = 1.f;
	static double time = 0.f;
	auto tar = m_cur->GetCursor();
	static CVector3 selectSize = { 0.8f,0.8f,0.8f };
	static CVector3 unselectSize = CVector3::One();
	m_leftSp->SetCollisionTarget(tar);
	m_rightSp->SetCollisionTarget(tar);
	if (m_leftSp->isCollidingTarget()) {
		m_leftSp->SetScale(selectSize);
	}
	else {
		m_leftSp->SetScale(unselectSize);
	}
	if (m_rightSp->isCollidingTarget()) {
		m_rightSp->SetScale(selectSize);
	}
	else {
		m_rightSp->SetScale(unselectSize);
	}
	if (m_leftSp->isCollidingTarget() && Mouse::isTrigger(enLeftClick) && time == 0.f) {
		if (m_selectedNum == 1) {
			return;
		}
		auto se = NewGO<Sound>(0);
		se->Init(L"Assets/sound/se/button.wav", false);
		se->Play();

		left = true;
		if(addPos.x == 0.f)
			m_selectedNum--;
	}
	if (m_rightSp->isCollidingTarget() && Mouse::isTrigger(enLeftClick) && time == 0.f) {
		if (m_selectedNum == m_numDungeon) {
			return;
		}
		auto se = NewGO<Sound>(0);
		se->Init(L"Assets/sound/se/button.wav", false);
		se->Play();
		right = true;
		if (addPos.x == 0.f)
			m_selectedNum++;
	}
	if (left) {
		time += 0.1f;
		if (time >= duration) {
			left = false;
			time = 0.f;
		}
		addPos.x = EASE::InOutQuad(change, 0.f, duration, time);
	}
	if (right) {
		time += 0.1f;
		if (time >= duration) {
			right = false;
			time = 0.f;
		}
		addPos.x = EASE::InOutQuad(change, 0.f, duration, time) * -1;
	}
	m_isPositionUpdating = left || right;

	//char str[256];
	//sprintf_s(str, "addpos.x %f\n", addPos.x);
	//OutputDebugStringA(str);
}

void DungeonSelect::StartDungeon() {
	if (m_isPositionUpdating || /*m_backSp->isCollidingTarget()*/m_returnButton->isFade())
		return;
	for (auto i : m_sps) {
		i->SetCollisionTarget(m_cur->GetCursor());
		if (Mouse::isTrigger(enLeftClick) and !m_isfade) {
			if (i->isCollidingTarget()) {
				dunNum = m_dungeonButton[i];
				if (dunNum > m_clearedDunNum + 1)
					return;
				m_fade->FadeOut();
				m_isfade = true;
				auto se = NewGO<Sound>(0);
				se->Init(L"Assets/sound/se/button.wav", false);
				se->Play();
			}
		}
	}
	if (m_isfade && m_fade->isFadeStop()) {
		auto dunAi = NewGO<DungeonAISelect>(0, "pvp");
		dunAi->SetDungeonNumber(dunNum);
		IDungeonData().SetDunNum(dunNum);
		IDungeonData().SetRound(0);
		DeleteGO(this);
	}
}

void DungeonSelect::BackToMenu() {
	if(!m_isfade and !m_backfade)
		m_returnButton->UpdateEx<ModeSelect>();

	/*m_backSp->SetCollisionTarget(m_cur->GetCursor());
	if (Mouse::isTrigger(enLeftClick) && m_backSp->isCollidingTarget()) {
		m_fade->FadeOut();
		m_backfade = true;
	}
	if (m_fade->isFadeStop() && m_backfade) {
		NewGO<ModeSelect>(0);
		DeleteGO(this);
	}*/
}

