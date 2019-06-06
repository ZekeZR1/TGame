#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"
#include "AIEdtiNodeAbnormalState.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeOrder.h"
#include "AIEditNodeProcess.h"

AIEditNodeAbnormalState::~AIEditNodeAbnormalState()
{

	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	for (auto fonts : m_font)
		DeleteGO(fonts);
}



bool AIEditNodeAbnormalState::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	m_spriteRender = NewGO<SpriteRender>(9, "target");
	m_spriteRender->Init(L"Assets/sprite/menu2.dds", 175, 275);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	//cursorpos.x += 135.0f;
	cursorpos.x += 87.5f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標


	for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
		m_aieditnodebutton = NewGO<AIEditNodeButton>(10, "button");
		m_aieditnodebutton->SetPri(10);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}

	//フォント
	for (int i = 0; i < button; i++) {
		m_fonts.push_back(NewGO<FontRender>(11));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}

	auto bacon = m_nodebuttons[0]->GetPos();
	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 40.f;
	m_fontpos.y = bacon.y + 107.f;
	m_fonts[0]->Init(L"どく", { m_fontpos }, 0.0, CVector4::White, scale, { 0.0,0.0 });
	m_fonts[0]->DrawShadow({ 5,-5 });
	m_fontpos.x -= 20.f;
	m_fontpos.y -= 57.f;
	m_fonts[1]->Init(L"やけど", { m_fontpos }, 0.0, CVector4::White, scale, { 0.0,0.0 });
	m_fonts[1]->DrawShadow({ 5,-5 });
	m_fontpos.y -= 55.f;
	m_fonts[2]->Init(L"こおり", { m_fontpos }, 0.0, CVector4::White, scale, { 0.0,0.0 });
	m_fonts[2]->DrawShadow({ 5,-5 });
	m_fontpos.x += 20.f;
	m_fontpos.y -= 55.f;
	m_fonts[3]->Init(L"まひ", { m_fontpos }, 0.0, CVector4::White, scale, { 0.0,0.0 });
	m_fonts[3]->DrawShadow({ 5,-5 });


	m_font.push_back(NewGO<FontRender>(3));
	m_font[0]->SetTextType(CFont::en_Japanese);

	return true;
}


void AIEditNodeAbnormalState::Order()
{

	//if (Mouse::isTrigger(enLeftClick)) {	//左クリック
	if(Choice6 ==false){
		//m_aieditnodeorder = NewGO<AIEditNodeOrder>(0, "Order");
		m_aieditnodeprocess->CreateOrder();
		Choice6 = true;

		abnormalfont = true;
	}

	contact2 = true;
}

void AIEditNodeAbnormalState::FontsConfirmation()
{

	CVector2 m_fontpos1 = CVector2::Zero();
	m_fontpos1.x -= 72;
	m_fontpos1.y += 360;
	bool cont = true;

	if (m_nodebuttons[button - 4]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"がどく", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
		m_font[0]->DrawShadow({ 5,-5 });

		contact1 = true;
	}

	else if (m_nodebuttons[button - 3]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"がやけど", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
		m_font[0]->DrawShadow({ 5,-5 });

		contact1 = true;
	}

	else if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"がこおり", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
		m_font[0]->DrawShadow({ 5,-5 });

		contact1 = true;
	}

	else if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"がまひ", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
		m_font[0]->DrawShadow({ 5,-5 });

		contact1 = true;
	}

	else {
		cont = false;
	}


	if (contact1 == true) {
		if (cont == false) {
			m_font[0]->Init(L"", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
			contact1 = false;
		}
	}

}

void AIEditNodeAbnormalState::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}

	if (contact2 == false) {
		FontsConfirmation();
	}

	if (Choice6 == false) { //何も選択していないとき

		if (Mouse::isTrigger(enLeftClick)) {	//左クリック

			if (m_nodebuttons[button - 4]->GetSpriteRender()->isCollidingTarget()) {
				m_abnormal = endoku;
				m_aieditnodeprocess->Setkeepabnormal(endoku);
				Order();
				PlayButtonSE();

			}
			if (m_nodebuttons[button - 3]->GetSpriteRender()->isCollidingTarget()) {
				m_abnormal = enyakedo;
				m_aieditnodeprocess->Setkeepabnormal(enyakedo);
				Order();
				PlayButtonSE();

			}
			if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
				m_abnormal = enhyouketu;
				m_aieditnodeprocess->Setkeepabnormal(enhyouketu);
				Order();
				PlayButtonSE();

			}
			if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
				m_abnormal = ensutan;
				m_aieditnodeprocess->Setkeepabnormal(ensutan);
				Order();
				PlayButtonSE();

			}

		}
	}

}