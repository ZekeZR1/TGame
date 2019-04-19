#include "stdafx.h"
#include "../GameCursor.h"
#include "CRatingSystem.h"
#include "RatePopup.h"

bool RatePopup::Start() {
	m_cursor = NewGO<GameCursor>(5);
	m_backsp = NewGO<SpriteRender>(5);
	m_backsp->Init(L"Assets/Sprite/popupback.dds", m_popupSca.x, m_popupSca.y);
	m_closesp = NewGO<SpriteRender>(5);
	m_closesp->Init(L"Assets/Sprite/button1.dds",200.f, 50.f, true);
	m_closesp->SetPosition({ 0.f,-250.f,0.f, });
	RateInit();
	return true;
}

void RatePopup::OnDestroy() {
	DeleteGO(m_backsp);
	DeleteGO(m_closesp);
	DeleteGO(m_info);
	DeleteGO(m_cursor);
	DeleteGO(m_myRate);
	DeleteGO(m_enemyRate);
}

void RatePopup::Update() {
	auto tar = m_cursor->GetCursor();
	m_closesp->SetCollisionTarget(tar);
	if (m_closesp->isCollidingTarget()) {
		if (Mouse::isTrigger(enLeftClick)) {
			DeleteGO(this);
		}
	}
}

void RatePopup::RateInit() {
	//info
	m_info = NewGO<FontRender>(5);
	m_info->SetTextType(CFont::en_Japanese);
	m_info->Init(L"Ÿ—¦", { -100.f,250.f });
	//m_info->SetPosition()
	m_info->DrawShadow();
	//my rate
	m_myRate = NewGO<FontRender>(5);
	//m_myRate->SetTextType(CFont::en_Japanese);
	std::wstring str = L"You\n  ";
	str += std::_Floating_to_wstring(L"%.2f", RatingSystem().GetWinRate());
	str += L"%";
	const wchar_t* wstr = str.c_str();
	m_myRate->Init(wstr);
	m_myRate->DrawShadow();
	m_myRate->SetPosition(m_myRatePos);
	//enemy rate
	m_enemyRate = NewGO<FontRender>(5);
	//m_enemyRate->SetTextType(CFont::en_Japanese);
	std::wstring estr = L"Enemy\n  ";
	estr += std::_Floating_to_wstring(L"%.2f", RatingSystem().GetEnemyRate());
	estr += L"%";
	const wchar_t* ewstr = estr.c_str();
	m_enemyRate->Init(ewstr);
	m_enemyRate->DrawShadow();
	m_enemyRate->SetPosition(m_enemyRatePos);
}