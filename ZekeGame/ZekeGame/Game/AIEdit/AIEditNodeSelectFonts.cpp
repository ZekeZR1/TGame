#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeSelectFonts.h"
#include "AIEditNodeTarget.h"
#include "AIEditNode.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeTechnique.h"
#include "AIEdtiNodeAbnormalState.h"

AIEditNodeSelectFonts::~AIEditNodeSelectFonts()
{
	for (auto fonts : m_fonts)
		DeleteGO(fonts);

}

bool AIEditNodeSelectFonts::Start()
{
	for (int i = 0; i < 6; i++) {
		m_fonts.push_back(NewGO<FontRender>(3));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}
	return true;
}

void AIEditNodeSelectFonts::FontsDisplay()
{

	if (m_aieditnodetarget != nullptr) {
		if (m_aieditnodetarget->Getfonttarget() == true && target == true) {
			CVector2 m_fontpos1 = CVector2::Zero();
			m_fontpos1.x = m_pos.x - 180;
			m_fontpos1.y = m_pos.y + 360;

			if (m_aieditnodetarget->GetTarget() == 100) {
				m_fonts[0]->Init(L"じぶん", { m_fontpos1 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[0]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodetarget->GetTarget() == 101) {
				m_fonts[0]->Init(L"みかた", { m_fontpos1 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[0]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodetarget->GetTarget() == 102) {
				m_fonts[0]->Init(L"てき", { m_fontpos1 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[0]->DrawShadow({ 5,-5 });
			}
			target = false;
		}
	}

	if (m_aieditnode != nullptr) {
		if (m_aieditnode->Getnodefont() == true && node == true) {
			CVector2 m_fontpos2 = CVector2::Zero();
			m_fontpos2.x = m_pos.x - 72;
			m_fontpos2.y = m_pos.y + 360;
			if (m_aieditnode->GetNode() == 200) {
				m_fonts[1]->Init(L"のHPが", { m_fontpos2 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[1]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnode->GetNode() == 201) {
				m_fonts[1]->Init(L"のMPが", { m_fontpos2 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[1]->DrawShadow({ 5,-5 });
			}
			node = false;
		}
	}

	if (m_aieditnodeinequ != nullptr) {
		if (m_aieditnodeinequ->Getinequfont() == true && inequ == true) {
			CVector2 m_fontpos3 = CVector2::Zero();
			m_fontpos3.x = m_pos.x + 181;
			m_fontpos3.y = m_pos.y + 360;
			if (m_aieditnodeinequ->GetInequ() == 300) {
				m_fonts[2]->Init(L"以上", { m_fontpos3 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[2]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodeinequ->GetInequ() == 301) {
				m_fonts[2]->Init(L"以下", { m_fontpos3 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[2]->DrawShadow({ 5,-5 });
			}
			inequ = false;
		}
	}

	if (m_aieditnodenum != nullptr) {
		if (m_aieditnodenum->Getnumfont() == true && num == true) {
			CVector2 m_fontpos4 = CVector2::Zero();
			m_fontpos4.x = m_pos.x + 63;
			m_fontpos4.y = m_pos.y + 360;
			if (m_aieditnodenum->GetNum() == 400) {
				m_fonts[3]->Init(L"1％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[3]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodenum->GetNum() == 401) {
				m_fonts[3]->Init(L"10％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[3]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodenum->GetNum() == 402) {
				m_fonts[3]->Init(L"30％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[3]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodenum->GetNum() == 403) {
				m_fonts[3]->Init(L"50％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[3]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodenum->GetNum() == 404) {
				m_fonts[3]->Init(L"70％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[3]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodenum->GetNum() == 405) {
				m_fonts[3]->Init(L"90％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[3]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodenum->GetNum() == 406) {
				m_fonts[3]->Init(L"100％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[3]->DrawShadow({ 5,-5 });
			}
			num = false;
		}
	}

	if (m_aieditnodetechnique != nullptr) {
		if (m_aieditnodetechnique->Gettechniquefont() == true && technique == true) {
			CVector2 m_fontpos5 = CVector2::Zero();
			m_fontpos5.x = m_pos.x - 180;
			m_fontpos5.y = m_pos.y + 360;
			if (m_aieditnodetechnique->Gettechnique() == 500) {
				m_fonts[4]->Init(L"　　　に　こうげき", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[4]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodetechnique->Gettechnique() == 501) {
				m_fonts[4]->Init(L"　　　から　にげる", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[4]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodetechnique->Gettechnique() == 502) {
				m_fonts[4]->Init(L"　　　を　ついせき", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[4]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodetechnique->Gettechnique() == 503) {
				m_fonts[4]->Init(L"ーーーまもる", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[4]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodetechnique->Gettechnique() == 504) {
				m_fonts[4]->Init(L"　　　を　かいふく", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[4]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodetechnique->Gettechnique() == 505) {
				m_fonts[4]->Init(L"　　　に　とくしゅ１", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[4]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodetechnique->Gettechnique() == 506) {
				m_fonts[4]->Init(L"　　　に　とくしゅ２", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[4]->DrawShadow({ 5,-5 });
			}

			technique = false;
		}
	}

	if (m_aieditnodeabnormalstate != nullptr) {
		if (m_aieditnodeabnormalstate->Getabnormalfont() == true && abnormal == true) {
			CVector2 m_fontpos6 = CVector2::Zero();
			m_fontpos6.x = m_pos.x - 72;
			m_fontpos6.y = m_pos.y + 360;
			if (m_aieditnodeabnormalstate->GetAbnormal() == 600) {
				m_fonts[5]->Init(L"が　どく", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[5]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodeabnormalstate->GetAbnormal() == 601) {
				m_fonts[5]->Init(L"が　やけど", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[5]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodeabnormalstate->GetAbnormal() == 602) {
				m_fonts[5]->Init(L"が　こおり", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[5]->DrawShadow({ 5,-5 });
			}
			if (m_aieditnodeabnormalstate->GetAbnormal() == 603) {
				m_fonts[5]->Init(L"が　まひ", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
				m_fonts[5]->DrawShadow({ 5,-5 });
			}

			abnormal = false;
		}

	}

}

void AIEditNodeSelectFonts::Update()
{
	m_aieditnodeabnormalstate = FindGO<AIEditNodeAbnormalState>("Abnormal");
	m_aieditnodetechnique = FindGO<AIEditNodeTechnique>("Technique");
	m_aieditnode = FindGO<AIEditNode>("firstwin");
	m_aieditnodeinequ = FindGO<AIEditNodeInequ>("Inequality");
	m_aieditnodenum = FindGO<AIEditNodeNum>("Num");
	m_aieditnodetarget = FindGO<AIEditNodeTarget>("target");

	FontsDisplay();
	
}