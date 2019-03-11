//4
#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeClick.h"
#include "AIEditLine.h"
#include "AIEditNodeTarget.h"
#include "../GameCursor.h"

#include "AIEditNodeOrder.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeTechnique.h"
#include "AIEdtiNodeAbnormalState.h"
AIEditNodeOrder::~AIEditNodeOrder()
{
	DeleteGO(m_spriteRender);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}

bool AIEditNodeOrder::Start()
{
	
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeclick = FindGO<AIEditNodeClick>("click");
	m_aieditnode = FindGO<AIEditNode>("firstwin");
	m_aieditnodeinequ = FindGO<AIEditNodeInequ>("Inequality");
	m_aieditnodenum = FindGO<AIEditNodeNum>("Num");
	m_aieditnodetarget = FindGO<AIEditNodeTarget>("target");
	m_aieditline = FindGO<AIEditLine>("Line");
	m_aieditnodeabnormalstate = FindGO<AIEditNodeAbnormalState>("Abnormal");
	m_aieditnodetechnique = FindGO<AIEditNodeTechnique>("Technique");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	
	CVector3 v = CVector3::Zero();
	QueryGOs<AIEditLine>("Line", [&](auto go)->bool
	{
		v = go->GetPos();
		return true;
	});
	m_pos = v;

	m_pos.x += 300;

	if (m_aieditnodeprocess->GetClickFlag() == false) {                                   //ClickÇ™Ç†ÇÈÇ∆Ç´ÅB
		m_pos = m_aieditnodeclick->GetPosition();
		m_pos.x += 30;
	}


	m_spriteRender = NewGO<SpriteRender>(2, "mass");
	m_spriteRender->Init(L"Assets/sprite/masss.dds", 300, 115);  //last
	m_spriteRender->SetPosition(m_pos);
	m_aieditnodeprocess->SetClickFlag(true);

	//ãZÇëIëÇµÇΩÇÁèoÇ»Ç¢ÇÊÇ§Ç…Ç∑ÇÈÅB
	if(Technique == false){
		m_aieditline = NewGO<AIEditLine>(0, "Line");
		m_aieditline->SetPos(m_pos);
	//	Fonts();
	}

	Fonts();
	DeleteGOs();


	return true;

}

void AIEditNodeOrder::Fonts()
{

	//ÉtÉHÉìÉg
	for (int i = 0; i < 6; i++) {
		m_fonts.push_back(NewGO<FontRender>(3));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}

	auto bacon = m_pos;

	if (m_aieditnodetarget != nullptr) {
		CVector2 m_fontpos1 = CVector2::Zero();
		m_fontpos1.x = m_pos.x - 120;
		m_fontpos1.y = m_pos.y + 45;
		if (m_aieditnodetarget->GetTarget() == 100) {
			m_fonts[0]->Init(L"é©ï™", { m_fontpos1 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodetarget->GetTarget() == 101) {
			m_fonts[0]->Init(L"ñ°ï˚", { m_fontpos1 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodetarget->GetTarget() == 102) {
			m_fonts[0]->Init(L"ìG", { m_fontpos1 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
	}

	if (m_aieditnode != nullptr) {
		CVector2 m_fontpos2 = CVector2::Zero();
		m_fontpos2.x = m_pos.x - 120;
		m_fontpos2.y = m_pos.y + 5;
		if (m_aieditnode->GetNode() == 200) {
			m_fonts[1]->Init(L"HP", { m_fontpos2 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnode->GetNode() == 201) {
			m_fonts[1]->Init(L"MP", { m_fontpos2 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
	}

	if (m_aieditnodeinequ != nullptr) {
		CVector2 m_fontpos3 = CVector2::Zero();
		m_fontpos3.x = m_pos.x + 30;
		m_fontpos3.y = m_pos.y + 5;
		if (m_aieditnodeinequ->GetInequ() == 300) {
			m_fonts[2]->Init(L"à»è„", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodeinequ->GetInequ() == 301) {
			m_fonts[2]->Init(L"à»â∫", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
	}

	if (m_aieditnodenum != nullptr) {
		CVector2 m_fontpos4 = CVector2::Zero();
		m_fontpos4.x = m_pos.x - 75;
		m_fontpos4.y = m_pos.y + 5;
		if (m_aieditnodenum->GetNum() == 400) {
			m_fonts[3]->Init(L"1Åì", { m_fontpos4 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodenum->GetNum() == 401) {
			m_fonts[3]->Init(L"10Åì", { m_fontpos4 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodenum->GetNum() == 402) {
			m_fonts[3]->Init(L"30Åì", { m_fontpos4 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodenum->GetNum() == 403) {
			m_fonts[3]->Init(L"50Åì", { m_fontpos4 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodenum->GetNum() == 404) {
			m_fonts[3]->Init(L"70Åì", { m_fontpos4 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodenum->GetNum() == 405) {
			m_fonts[3]->Init(L"90Åì", { m_fontpos4 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodenum->GetNum() == 406) {
			m_fonts[3]->Init(L"100Åì", { m_fontpos4 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
	}

	if (m_aieditnodetechnique != nullptr) {
		CVector2 m_fontpos5 = CVector2::Zero();
		m_fontpos5.x = m_pos.x - 45;
		m_fontpos5.y = m_pos.y + 5;
		if (m_aieditnodetechnique->Gettechnique() == 500) {
			m_fonts[4]->Init(L"çUåÇ", { m_fontpos5 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 501) {
			m_fonts[4]->Init(L"ì¶Ç∞ÇÈ", { m_fontpos5 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 502) {
			m_fonts[4]->Init(L"í«ê’", { m_fontpos5 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 503) {
			m_fonts[4]->Init(L"éÁÇÈ", { m_fontpos5 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 504) {
			m_fonts[4]->Init(L"âÒïú", { m_fontpos5 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 505) {
			m_fonts[4]->Init(L"ì¡éÍãZÇP", { m_fontpos5 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 506) {
			m_fonts[4]->Init(L"ì¡éÍãZÇQ", { m_fontpos5 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
	}

	if (m_aieditnodeabnormalstate != nullptr) {
		CVector2 m_fontpos6 = CVector2::Zero();
		m_fontpos6.x = m_pos.x - 25;
		m_fontpos6.y = m_pos.y + 5;
		if (m_aieditnodeabnormalstate->GetAbnormal() == 600) {
			m_fonts[5]->Init(L"ì≈", { m_fontpos6 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodeabnormalstate->GetAbnormal() == 601) {
			m_fonts[5]->Init(L"âŒèù", { m_fontpos6 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodeabnormalstate->GetAbnormal() == 602) {
			m_fonts[5]->Init(L"ïXåã", { m_fontpos6 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
		if (m_aieditnodeabnormalstate->GetAbnormal() == 603) {
			m_fonts[5]->Init(L"ÉXÉ^Éì", { m_fontpos6 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
		}
	}

}



void AIEditNodeOrder::DeleteGOs()
{

	if (m_aieditnodetarget != nullptr) {
		DeleteGO(m_aieditnodetarget);
		m_aieditnodetarget = nullptr;
	}

	if (m_aieditnode != nullptr) {
		DeleteGO(m_aieditnode);
		m_aieditnode = nullptr;
	}

	if (m_aieditnodeinequ != nullptr) {
		DeleteGO(m_aieditnodeinequ);
		m_aieditnodeinequ = nullptr;
	}

	if (m_aieditnodenum != nullptr) {
		DeleteGO(m_aieditnodenum);
		m_aieditnodenum = nullptr;
	}

	if (m_aieditnodeclick != nullptr) {
		DeleteGO(m_aieditnodeclick);
		m_aieditnodeclick = nullptr;
	}

	if (m_aieditnodeabnormalstate != nullptr) {
		DeleteGO(m_aieditnodeabnormalstate);
		m_aieditnodeabnormalstate = nullptr;
	}

	if (m_aieditnodetechnique != nullptr) {
		DeleteGO(m_aieditnodetechnique);
		m_aieditnodetechnique = nullptr;
		//ClickÇï\é¶Ç∑ÇÈÅB
		m_aieditnodeprocess->Click();

		m_aieditnodeprocess->SetClickFlag(false);
	}
}

void AIEditNodeOrder::Update()
{


}