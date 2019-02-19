#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"
#include "AIEdtiNodeAbnormalState.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeOrder.h"

AIEditNodeAbnormalState::~AIEditNodeAbnormalState()
{

	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}



bool AIEditNodeAbnormalState::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

	m_spriteRender = NewGO<SpriteRender>(0, "target");
	m_spriteRender->Init(L"Assets/sprite/sieat.dds", 150, 250);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標


	for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
		m_aieditnodebutton = NewGO<AIEditNodeButton>(4, "button");
		m_aieditnodebutton->SetPri(4);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}

	//フォント
	for (int i = 0; i < button; i++) {
		m_fonts.push_back(NewGO<FontRender>(5));
	}
	auto bacon = m_nodebuttons[0]->GetPos();
	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 50.0;
	m_fontpos.y = bacon.y + 110.0;
	m_fonts[0]->Init(L" 毒", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[1]->Init(L"火傷", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x -= 20.f;
	m_fontpos.y -= 55.f;
	m_fonts[2]->Init(L" 氷結", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x -= 14.f;
	m_fontpos.y -= 55.f;
	m_fonts[3]->Init(L" スタン", { m_fontpos }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	return true;
}


void AIEditNodeAbnormalState::Order()
{

	if (Mouse::isTrigger(enLeftClick)) {	//左クリック
		m_aieditnodeorder = NewGO<AIEditNodeOrder>(0, "Order");
		Choice6 = true;
	}
}


void AIEditNodeAbnormalState::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}

	if (Choice6 == false) { //何も選択していないとき

		for (int i = 0; i < button; i++) {
			if (m_nodebuttons[i]->GetSpriteRender()->isCollidingTarget())	//選択しているか	
			{
				Order();

			}

		}

	}

}