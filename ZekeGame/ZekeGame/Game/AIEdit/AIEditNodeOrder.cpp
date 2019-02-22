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

	if (m_aieditnodeprocess->GetClickFlag() == false) {                                   //Clickがあるとき。
		m_pos = m_aieditnodeclick->GetPosition();
		m_pos.x += 30;
	}


	m_spriteRender = NewGO<SpriteRender>(8, "mass");
	m_spriteRender->Init(L"Assets/sprite/masss.dds", 300, 120);  //last
	m_spriteRender->SetPosition(m_pos);
	m_aieditnodeprocess->SetClickFlag(true);

	//技を選択したら出ないようにする。
	if(Technique == false){
		m_aieditline = NewGO<AIEditLine>(0, "Line");
		m_aieditline->SetPos(m_pos);
		Fonts();
	}

	
	DeleteGOs();


	return true;

}

void AIEditNodeOrder::Fonts()
{

	//フォント
	for (int i = 0; i < 6; i++) {
		m_fonts.push_back(NewGO<FontRender>(9));
	}

	auto bacon = m_pos;
	CVector2 m_fontpos1 = CVector2::Zero();
	m_fontpos1.x = m_pos.x - 120;
	m_fontpos1.y = m_pos.y + 45;
	if (m_aieditnodetarget->GetTarget() == 100) {
		m_fonts[0]->Init(L"自分", { m_fontpos1 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodetarget->GetTarget() == 101) {
		m_fonts[0]->Init(L"味方", { m_fontpos1 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodetarget->GetTarget() == 102) {
		m_fonts[0]->Init(L"敵", { m_fontpos1 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}

	CVector2 m_fontpos2 = CVector2::Zero();
	m_fontpos2.x = m_pos.x - 100;
	m_fontpos2.y = m_pos.y + 5;
	if (m_aieditnode->GetNode() == 200) {
		m_fonts[1]->Init(L"HP", { m_fontpos2 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnode->GetNode() == 201) {
		m_fonts[1]->Init(L"MP", { m_fontpos2 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}

	CVector2 m_fontpos3 = CVector2::Zero();
	m_fontpos3.x = m_pos.x;
	m_fontpos3.y = m_pos.y + 5;
	if (m_aieditnodeinequ->GetInequ() == 300) {
		m_fonts[2]->Init(L"以上", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodeinequ->GetInequ() == 301) {
		m_fonts[2]->Init(L"以下", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}

	CVector2 m_fontpos4 = CVector2::Zero();
	m_fontpos4.x = m_pos.x - 50;
	m_fontpos4.y = m_pos.y + 5;
	if (m_aieditnodenum->GetNum() == 400) {
		m_fonts[7]->Init(L"1％", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodenum->GetNum() == 401) {
		m_fonts[6]->Init(L"10％", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodenum->GetNum() == 402) {
		m_fonts[5]->Init(L"30％", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodenum->GetNum() == 403) {
		m_fonts[4]->Init(L"50％", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodenum->GetNum() == 404) {
		m_fonts[3]->Init(L"70％", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodenum->GetNum() == 405) {
		m_fonts[2]->Init(L"90％", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	}
	if (m_aieditnodenum->GetNum() == 406) {
		m_fonts[1]->Init(L"100％", { m_fontpos3 }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
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
		//Clickを表示する。
		m_aieditnodeprocess->Click();

		m_aieditnodeprocess->SetClickFlag(false);
	}
}

void AIEditNodeOrder::Update()
{


}