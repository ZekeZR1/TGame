#include "stdafx.h"
#include "../GameCursor.h"

#include "AIEditNodeTechnique.h"
//camera
#include "../../GameCamera.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeOrder.h"
#include "AIEditNodeProcess.h"

AIEditNodeTechnique ::~AIEditNodeTechnique()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}




bool AIEditNodeTechnique::Start()
{

	m_gamecursor = FindGO<GameCursor>("cursor");
	m_spriteRender = NewGO<SpriteRender>(6, "Technique");	
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_spriteRender->Init(L"Assets/sprite/menu2.dds", 175, 470);
	m_spriteRender->SetPivot({ 0.5f, 0.67f });
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	//cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標

	//ボタン
	for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
		m_aieditnodebutton = NewGO<AIEditNodeButton>(7, "button");
		m_aieditnodebutton->SetPri(7);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}


	//フォント
	for (int i = 0; i < button; i++) {
		m_fonts.push_back(NewGO<FontRender>(8));
	}
	auto bacon = m_nodebuttons[0]->GetPos();
	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 50.0;
	m_fontpos.y = bacon.y + 110.0;
	m_fonts[0]->Init(L"攻撃", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x -= 12.f;
	m_fontpos.y -= 57.f;
	m_fonts[1]->Init(L"逃げる", { m_fontpos }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fontpos.x += 12.f;
	m_fontpos.y -= 55.f;
	m_fonts[2]->Init(L"追跡", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[3]->Init(L"守る", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[4]->Init(L"回復", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x -= 10.f;
	m_fontpos.y -= 65.f;
	m_fonts[5]->Init(L"特殊技1", { m_fontpos }, 0.0, CVector4::White, 0.7, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[6]->Init(L"特殊技2", { m_fontpos }, 0.0, CVector4::White, 0.7, { 0.0,0.0 });

	return true;
}

void AIEditNodeTechnique::Order()
{

	//if (Mouse::isTrigger(enLeftClick)) {	//左クリック
	if(Choice4==false){
		m_aieditnodeorder = NewGO<AIEditNodeOrder>(0, "Order");
		Choice4 = true;
		m_aieditnodeorder->SetTec(true);
	}
}

void AIEditNodeTechnique::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}


	if (Mouse::isTrigger(enLeftClick)) {	//左クリック

		if (m_nodebuttons[button - 7]->GetSpriteRender()->isCollidingTarget()) {
			m_technique = enAttak;
			m_aieditnodeprocess->Setkeeptechnique(enAttak);
			Order();
		}

		if (m_nodebuttons[button - 6]->GetSpriteRender()->isCollidingTarget()) {
			m_technique = enEscape;
			m_aieditnodeprocess->Setkeeptechnique(enEscape);
			Order();
		}

		if (m_nodebuttons[button - 5]->GetSpriteRender()->isCollidingTarget()) {
			m_technique = enCase;
			m_aieditnodeprocess->Setkeeptechnique(enCase);
			Order();
		}

		if (m_nodebuttons[button - 4]->GetSpriteRender()->isCollidingTarget()) {
			m_technique = enProtect;
			m_aieditnodeprocess->Setkeeptechnique(enProtect);
			Order();
		}

		if (m_nodebuttons[button - 3]->GetSpriteRender()->isCollidingTarget()) {
			m_technique = enHeel;
			m_aieditnodeprocess->Setkeeptechnique(enHeel);
			Order();
		}

		if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
			m_technique = enSpecial1;
			m_aieditnodeprocess->Setkeeptechnique(enSpecial1);
			Order();
		}

		if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
			m_technique = enSpecial2;
			m_aieditnodeprocess->Setkeeptechnique(enSpecial2);
			Order();
		}
	}
}
