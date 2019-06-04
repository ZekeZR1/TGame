#include "stdafx.h"
#include "../GameCursor.h"
#include "CRatingSystem.h"
#include "RatePopup.h"

bool RatePopup::Start() {
	if (m_isShowMyRate)
		InitMyInfo();
	if (m_isShowEnemyRate)
		InitEnemyInfo();
	m_backsp = NewGO<SpriteRender>(5);
	m_backsp->Init(L"Assets/Sprite/popupback.dds", m_popupSca.x, m_popupSca.y);

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
	//TODO 
	/*auto tar = m_cursor->GetCursor();
	m_closesp->SetCollisionTarget(tar);
	if (m_closesp->isCollidingTarget()) {
		if (Mouse::isTrigger(enLeftClick)) {
			DeleteGO(this);
		}
	}*/
}

void RatePopup::RateInit() {
	//info
	m_info = NewGO<FontRender>(5);
	m_info->SetTextType(CFont::en_Japanese);
	m_info->Init(L"勝率", { -100.f,250.f });
	//m_info->SetPosition()
	m_info->DrawShadow();
	//my rate
	m_myRate = NewGO<FontRender>(5);
	//m_myRate->SetTextType(CFont::en_Japanese);
	std::wstring str = L"You\n  ";
	str += std::_Floating_to_wstring(L"%.2f", RatingSystem().GetWinRate());
	//str += std::_Floating_to_wstring(L"%.2f", m_eneRating);
	str += L"%";
	const wchar_t* wstr = str.c_str();
	m_myRate->Init(wstr);
	m_myRate->DrawShadow();
	m_myRate->SetPosition(m_myRatePos);
	//enemy rate
	m_enemyRate = NewGO<FontRender>(5);
	//m_enemyRate->SetTextType(CFont::en_Japanese);
	std::wstring estr = L"Enemy\n  ";
	char ss[256];
	//float content = m_eneRating;
	float content = RatingSystem().GetEnemyRate();
	sprintf_s(ss, "ENEMEYYYYYYY  Rate  IS %f [ POPUP TIMING]\n", content);
	estr += std::_Floating_to_wstring(L"%.2f", content);
	estr += L"%";
	const wchar_t* ewstr = estr.c_str();
	m_enemyRate->Init(ewstr);
	m_enemyRate->DrawShadow();
	m_enemyRate->SetPosition(m_enemyRatePos);
}

void RatePopup::InitMyInfo() {

}

void RatePopup::InitEnemyInfo() {
	m_cursor = NewGO<GameCursor>(5);

}

//

bool RatingInfo::Start() {
	m_backsp = NewGO<SpriteRender>(5);
	m_backsp->Init(L"Assets/Sprite/syber1.dds", m_backSca.x * m_scale, m_backSca.y * m_scale);
	m_backsp->SetPosition(m_pos);

	m_info = NewGO<FontRender>(5);
	m_info->SetTextType(CFont::en_Japanese);
	m_info->Init(L"ステータス", { m_pos.x - 100 * m_scale, m_pos.y + 250.f * m_scale },0.f,CVector4::White,m_scale);
	//m_info->SetPosition()
	m_info->DrawShadow();
	//my rate
	m_myRate = NewGO<FontRender>(5);
	m_myRate->SetTextType(CFont::en_Japanese);
	std::wstring str = L"\n勝率\n ";
	str += std::_Floating_to_wstring(L"%.2f", RatingSystem().GetWinRate());
	//str += std::_Floating_to_wstring(L"%.2f", m_eneRating);
	str += L"%\n";
	str += L"\n試合数\n ";
	str += std::to_wstring(RatingSystem().GetTotalBattleNum());
	str += L"回\n";
	str += L"\n勝利数\n ";
	str += std::to_wstring(RatingSystem().GetTotalWinNum());
	const wchar_t* wstr = str.c_str();
	m_myRate->Init(wstr, { m_pos.x - 150.f  * m_scale ,m_pos.y + 200.f * m_scale }, 0.f, CVector4::White, m_scale);
	m_myRate->DrawShadow();
	return true;
}

void RatingInfo::Update() {

}

void RatingInfo::OnDestroy() {
	DeleteGO(m_backsp);
	DeleteGO(m_info);
	DeleteGO(m_myRate);
}