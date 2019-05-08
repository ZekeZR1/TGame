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
#include "AIEditNodeSelectFonts.h"
#include "AIEditNodeDeleteKey.h"
AIEditNodeOrder::~AIEditNodeOrder()
{
	DeleteGO(m_spriteRender);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	if (m_aieditnodedeletekey != nullptr) {
		DeleteGO(m_aieditnodedeletekey);
	}
	DeleteGO(m_aieditline);
}

bool AIEditNodeOrder::Start()
{
	if (m_isMakeOrder)
		return true;
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeclick = FindGO<AIEditNodeClick>("click");
	m_aieditnode = FindGO<AIEditNode>("firstwin");
	m_aieditnodeinequ = FindGO<AIEditNodeInequ>("Inequality");
	m_aieditnodenum = FindGO<AIEditNodeNum>("Num");
	m_aieditnodetarget = FindGO<AIEditNodeTarget>("target");
	m_aieditnodeabnormalstate = FindGO<AIEditNodeAbnormalState>("Abnormal");
	m_aieditnodetechnique = FindGO<AIEditNodeTechnique>("Technique");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_aieditonodeselectfonts = FindGO<AIEditNodeSelectFonts>("fonts");
	
	CVector3 v = CVector3::Zero();
	QueryGOs<AIEditLine>("Line", [&](auto go)->bool
	{
		v = go->GetPos();
		return true;
	});
	m_pos = v;

	m_pos.x += 300;

	//Clickがあるとき。
	if (m_aieditnodeprocess->GetClickFlag() == false) {                                  
		m_pos = m_aieditnodeclick->GetPosition();
		m_pos.x += 30;
	}

	m_spriteRender = NewGO<SpriteRender>(2, "mass");
	m_spriteRender->Init(L"Assets/sprite/masss.dds", 300, 115);  //last
	m_spriteRender->SetPosition(m_pos);
	m_aieditnodeprocess->SetClickFlag(true);

	//技を選択したらLineを出ないようにする。
	if(Technique == false){
		m_aieditline = NewGO<AIEditLine>(0, "Line");
		m_aieditline->SetPos(m_pos);
	}

	Fonts();
	DeleteGOs();

	return true;

}

AIEditNodeDeleteKey* AIEditNodeOrder::CreateDeleteKey()
{
	m_aieditnodedeletekey = NewGO<AIEditNodeDeleteKey>(5, "deletekey");
	m_aieditnodedeletekey->SetOrder(this);

	return m_aieditnodedeletekey;
}

void AIEditNodeOrder::Fonts()
{

	//フォント
	for (int i = 0; i < 6; i++) {
		m_fonts.push_back(NewGO<FontRender>(3));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}

	auto bacon = m_pos;

	if (m_aieditnodetarget != nullptr) {
		CVector2 m_fontpos1 = CVector2::Zero();
		m_fontpos1.x = m_pos.x - 120;
		m_fontpos1.y = m_pos.y + 38;
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
	}

	if (m_aieditnode != nullptr) {
		CVector2 m_fontpos2 = CVector2::Zero();
		m_fontpos2.x = m_pos.x - 120;
		//m_fontpos2.y = m_pos.y + 5;
		m_fontpos2.y = m_pos.y + 38;
		if (m_aieditnode->GetNode() == 200) {
			m_fonts[1]->Init(L"　　　の\nHP", { m_fontpos2 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[1]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnode->GetNode() == 201) {
			m_fonts[1]->Init(L"　　　の\nMP", { m_fontpos2 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[1]->DrawShadow({ 5,-5 });
		}
	}

	if (m_aieditnodeinequ != nullptr) {
		CVector2 m_fontpos3 = CVector2::Zero();
		m_fontpos3.x = m_pos.x + 35;
		m_fontpos3.y = m_pos.y + 0;
		if (m_aieditnodeinequ->GetInequ() == 300) {
			m_fonts[2]->Init(L"以上", { m_fontpos3 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[2]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodeinequ->GetInequ() == 301) {
			m_fonts[2]->Init(L"以下", { m_fontpos3 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[2]->DrawShadow({ 5,-5 });
		}
	}

	if (m_aieditnodenum != nullptr) {
		CVector2 m_fontpos4 = CVector2::Zero();
		m_fontpos4.x = m_pos.x - 65;
		m_fontpos4.y = m_pos.y + 0;
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
		}\
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
	}

	if (m_aieditnodetechnique != nullptr) {
		CVector2 m_fontpos5 = CVector2::Zero();
		m_fontpos5.x = m_pos.x - 120;
		m_fontpos5.y = m_pos.y + 38;
		if (m_aieditnodetechnique->Gettechnique() == 500) {
			m_fonts[4]->Init(L"　　　に\n　　こうげき", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 501) {
			m_fonts[4]->Init(L"　　　から\n　　にげる", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 502) {
			m_fonts[4]->Init(L"　　　を\n　ついせき", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 503) {
			m_fonts[4]->Init(L"ーーー\n　　まもる", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 504) {
			m_fonts[4]->Init(L"　　　を\n　　かいふく", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 505) {
			m_fonts[4]->Init(L"　　　に\n　　とくしゅ１", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodetechnique->Gettechnique() == 506) {
			m_fonts[4]->Init(L"　　　に\n　　とくしゅ２", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		techniqueOrder = true;

	}

	if (m_aieditnodeabnormalstate != nullptr) {
		CVector2 m_fontpos6 = CVector2::Zero();
		m_fontpos6.x = m_pos.x - 120;
		m_fontpos6.y = m_pos.y + 38;
		if (m_aieditnodeabnormalstate->GetAbnormal() == 600) {
			m_fonts[5]->Init(L"　　　が\n　　　どく", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[5]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodeabnormalstate->GetAbnormal() == 601) {
			m_fonts[5]->Init(L"　　　が\n　　　やけど", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[5]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodeabnormalstate->GetAbnormal() == 602) {
			m_fonts[5]->Init(L"　　　が\n　　　こおり", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[5]->DrawShadow({ 5,-5 });
		}
		if (m_aieditnodeabnormalstate->GetAbnormal() == 603) {
			m_fonts[5]->Init(L"　　　が\n　　　まひ", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[5]->DrawShadow({ 5,-5 });
		}
	}

}

//WindowをすべてDeleteするための関数。
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

	//if (m_aieditnodedeletekey != nullptr) {
	//	DeleteGO(m_aieditnodedeletekey);
	//	m_aieditnodedeletekey = nullptr;
	//}

	if (m_aieditnodetechnique != nullptr) {
		DeleteGO(m_aieditnodetechnique);
		m_aieditnodetechnique = nullptr;

		if (NextClickFlag == false) {
			//Clickを表示する。
			m_aieditnodeprocess->Click();

			m_aieditnodeprocess->SetClickFlag(false);
		}
	}
}


void AIEditNodeOrder::Update()
{

	if (timer == false) {
		if (fonttimer > 0) {
			fonttimer -= 1 * IGameTime().GetFrameDeltaTime();
		}

		if (fonttimer <= 0) {
			if (m_aieditonodeselectfonts != nullptr) {
				DeleteGO(m_aieditonodeselectfonts);
				m_aieditonodeselectfonts = nullptr;
			}
			timer = true;
		}
	}
}

void AIEditNodeOrder::makeOrder(int l,int o,sOrder* order, bool isEnd)
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeclick = FindGO<AIEditNodeClick>("click");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	m_aieditnodeprocess->setFlagkeep(l, o, 4, order->abn);
	m_aieditnodeprocess->setFlagkeep(l, o, 5, order->tec);
	m_aieditnodeprocess->setFlagkeep(l, o, 3, order->num);
	m_aieditnodeprocess->setFlagkeep(l, o, 2, order->ine);
	m_aieditnodeprocess->setFlagkeep(l, o, 1, order->nod);
	m_aieditnodeprocess->setFlagkeep(l, o, 0, order->tar);
	/*int vo = int(order);
	if (vo >= 600)
	{
		m_aieditnodeprocess->setFlagkeep(l, o, 4, vo);
	}
	else if (vo >= 500)
	{
		m_aieditnodeprocess->setFlagkeep(l, o, 5, vo);
	}
	else if (vo >= 400)
	{
		m_aieditnodeprocess->setFlagkeep(l, o, 3, vo);
	}
	else if (vo >= 300)
	{
		m_aieditnodeprocess->setFlagkeep(l, o, 2, vo);
	}
	else if (vo >= 200)
	{
		m_aieditnodeprocess->setFlagkeep(l, o, 1, vo);
	}
	else if (vo >= 100)
	{
		m_aieditnodeprocess->setFlagkeep(l, o, 0, vo);
	}*/

	CVector3 v = CVector3::Zero();
	QueryGOs<AIEditLine>("Line", [&](auto go)->bool
	{
		v = go->GetPos();
		return true;
	});
	m_pos = v;

	m_pos.x += 300;

	//Clickがあるとき。
	if (m_aieditnodeprocess->GetClickFlag() == false) {
		//m_pos = m_aieditnodeclick->GetPosition();
		//m_pos.x += 30;
	}
	CVector3 vp = { float(-400 + o * 420),float(275 - l * 85),0 };
	m_pos = vp;

	m_spriteRender = NewGO<SpriteRender>(2, "mass");
	m_spriteRender->Init(L"Assets/sprite/masss.dds", 300, 115);  //last
	m_spriteRender->SetPosition(m_pos);
	//m_aieditnodeprocess->SetClickFlag(true);

	//技を選択したらLineを出ないようにする。
	if (!isEnd) {
		m_aieditline = NewGO<AIEditLine>(0, "Line");
		m_aieditline->SetPos(m_pos);
		m_aieditline->makeLine();
		
	}
	else
	{
		CreateDeleteKey();
	}
	m_aieditnodeprocess->SetTechniqueGenerate(true);
	makeFonts(order);

	m_aieditnodeprocess->setOrderkeep(l, o, this);
	m_isMakeOrder = true;
}

void AIEditNodeOrder::makeFonts(sOrder* order)
{
	//フォント
	for (int i = 0; i < 6; i++) {
		m_fonts.push_back(NewGO<FontRender>(3));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}

	if (order->tar != 0)
	{
		CVector2 m_fontpos1 = CVector2::Zero();
		m_fontpos1.x = m_pos.x - 120;
		m_fontpos1.y = m_pos.y + 38;
		if (order->tar == 100) {
			m_fonts[0]->Init(L"じぶん", { m_fontpos1 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[0]->DrawShadow({ 5,-5 });
		}
		else if (order->tar == 101) {
			m_fonts[0]->Init(L"みかた", { m_fontpos1 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[0]->DrawShadow({ 5,-5 });
		}
		else if (order->tar == 102) {
			m_fonts[0]->Init(L"てき", { m_fontpos1 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[0]->DrawShadow({ 5,-5 });
		}
	}


	if (order->nod != 0)
	{
		CVector2 m_fontpos2 = CVector2::Zero();
		m_fontpos2.x = m_pos.x - 120;
		//m_fontpos2.y = m_pos.y + 5;
		m_fontpos2.y = m_pos.y + 38;
		if (order->nod == 200) {
			m_fonts[1]->Init(L"　　　の\nHP", { m_fontpos2 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[1]->DrawShadow({ 5,-5 });
		}
		else if (order->nod == 201) {
			m_fonts[1]->Init(L"　　　の\nMP", { m_fontpos2 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[1]->DrawShadow({ 5,-5 });
		}
	}


	if (order->ine != 0)
	{
		CVector2 m_fontpos3 = CVector2::Zero();
		m_fontpos3.x = m_pos.x + 35;
		m_fontpos3.y = m_pos.y + 0;
		if (order->ine == 300) {
			m_fonts[2]->Init(L"以上", { m_fontpos3 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[2]->DrawShadow({ 5,-5 });
		}
		else if (order->ine == 301) {
			m_fonts[2]->Init(L"以下", { m_fontpos3 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[2]->DrawShadow({ 5,-5 });
		}
	}


	if (order->num != 0)
	{
		CVector2 m_fontpos4 = CVector2::Zero();
		m_fontpos4.x = m_pos.x - 65;
		m_fontpos4.y = m_pos.y + 0;
		if (order->num == 400) {
			m_fonts[3]->Init(L"1％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[3]->DrawShadow({ 5,-5 });
		}
		else if (order->num == 401) {
			m_fonts[3]->Init(L"10％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[3]->DrawShadow({ 5,-5 });
		}
		else if (order->num == 402) {
			m_fonts[3]->Init(L"30％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[3]->DrawShadow({ 5,-5 });
		}
		else if (order->num == 403) {
			m_fonts[3]->Init(L"50％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[3]->DrawShadow({ 5,-5 });
		}
		else if (order->num == 404) {
			m_fonts[3]->Init(L"70％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[3]->DrawShadow({ 5,-5 });
		}
		else if (order->num == 405) {
			m_fonts[3]->Init(L"90％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[3]->DrawShadow({ 5,-5 });
		}
		else if (order->num == 406) {
			m_fonts[3]->Init(L"100％", { m_fontpos4 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[3]->DrawShadow({ 5,-5 });
		}
	}


	if (order->tec != 0)
	{
		CVector2 m_fontpos5 = CVector2::Zero();
		m_fontpos5.x = m_pos.x - 120;
		m_fontpos5.y = m_pos.y + 38;
		if (order->tec == 500) {
			m_fonts[4]->Init(L"　　　に\n　　こうげき", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		else if (order->tec == 501) {
			m_fonts[4]->Init(L"　　　から\n　　にげる", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		else if (order->tec == 502) {
			m_fonts[4]->Init(L"　　　を\n　ついせき", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		else if (order->tec == 503) {
			m_fonts[4]->Init(L"ーーー\n　　まもる", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		else if (order->tec == 504) {
			m_fonts[4]->Init(L"　　　を\n　　かいふく", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		else if (order->tec == 505) {
			m_fonts[4]->Init(L"　　　に\n　　とくしゅ１", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
		else if (order->tec == 506) {
			m_fonts[4]->Init(L"　　　に\n　　とくしゅ２", { m_fontpos5 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[4]->DrawShadow({ 5,-5 });
		}
	}


	if (order->abn != 0)
	{
		CVector2 m_fontpos6 = CVector2::Zero();
		m_fontpos6.x = m_pos.x - 120;
		m_fontpos6.y = m_pos.y + 38;
		if (order->abn == 600) {
			m_fonts[5]->Init(L"　　　が\n　　　どく", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[5]->DrawShadow({ 5,-5 });
		}
		else if (order->abn == 601) {
			m_fonts[5]->Init(L"　　　が\n　　　やけど", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[5]->DrawShadow({ 5,-5 });
		}
		else if (order->abn == 602) {
			m_fonts[5]->Init(L"　　　が\n　　　こおり", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[5]->DrawShadow({ 5,-5 });
		}
		else if (order->abn == 603) {
			m_fonts[5]->Init(L"　　　が\n　　　まひ", { m_fontpos6 }, 0.0, CVector4::White, scale, { 0.0,0.0 });
			m_fonts[5]->DrawShadow({ 5,-5 });
		}
	}
}
