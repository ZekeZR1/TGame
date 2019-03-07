//2
#include "stdafx.h"
#include "AIEditNodeInequ.h"

#include "../GameCursor.h"

#include "../../GameCamera.h"

#include "AIEditNode.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeProcess.h"

AIEditNodeInequ::~AIEditNodeInequ()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}

bool AIEditNodeInequ::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnode = FindGO<AIEditNode>("firstwin");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(9, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/menu2.dds", 175, 140);
	m_spriteRender->SetPivot({ 0.5f, 0.1f });
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標
	

	for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
		m_aieditnodebutton = NewGO<AIEditNodeButton>(10, "button ");
		m_aieditnodebutton->SetPri(10);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}

	//フォント
	for (int i = 0; i < button; i++) {
		m_fonts.push_back(NewGO<FontRender>(11));
	}
	auto bacon = m_nodebuttons[0]->GetPos();
	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 55.0;
	m_fontpos.y = bacon.y + 110.0;
	m_fonts[0]->Init(L"より大", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[1]->Init(L"より小", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	return true;

}



void AIEditNodeInequ::Num()
{
	if (Choice2 == false) { //何も選択していないとき
		m_aieditnodenum = NewGO<AIEditNodeNum>(0, "Num");

		Choice2 = true;
	}
	
}


void AIEditNodeInequ::Update()
{
	
	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}

	

	for (int i = 0; i < button; i++) {
		if (m_nodebuttons[i]->GetSpriteRender()->isCollidingTarget())	//選択しているか	
		{
			//Num();

		}

		if (Mouse::isTrigger(enLeftClick)) {	//左クリック
			if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
				m_inequ = enDainari;
				m_aieditnodeprocess->Setkeepinequ(enDainari);
				Num();
			}

			if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
				m_inequ = enShowers;
				m_aieditnodeprocess->Setkeepinequ(enShowers);
				Num();
			}

		}
		
	}
}