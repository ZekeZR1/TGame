#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"

#include "AIEditNodeTarget.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeTechnique.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeSelectFonts.h"
#include "AIEditNodeSelectFonts.h"

AIEditNodeTarget::~AIEditNodeTarget()
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

bool AIEditNodeTarget::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	m_spriteRender = NewGO<SpriteRender>(3, "target");
	m_spriteRender->Init(L"Assets/sprite/menu2.dds", 175, 205);
	m_spriteRender->SetPivot({ 0.5f, 0.35f });

	m_aieditnodeselectfonts = NewGO<AIEditNodeSelectFonts>(0, "fonts");

	m_position.x -= 300;
	m_position.y = 150;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標

	//ぼたん
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
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}

	auto bacon = m_nodebuttons[0]->GetPos();

	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 60.0;
	m_fontpos.y = bacon.y + 105.0;
	m_fonts[0]->Init(L"じぶん", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	m_fonts[0]->DrawShadow({ 5,-5 });
	m_fontpos.y -= 55.f;
	m_fonts[1]->Init(L"みかた", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	m_fonts[1]->DrawShadow({ 5,-5 });
	m_fontpos.x += 15.f;
	m_fontpos.y -= 55.f;
	m_fonts[2]->Init(L"てき", { m_fontpos }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
	m_fonts[2]->DrawShadow({ 5,-5 });
	
	m_font.push_back(NewGO<FontRender>(3));
	m_font[0]->SetTextType(CFont::en_Japanese);

	return true;
}

void AIEditNodeTarget::Num() 
{
	if (m_aieditnodeprocess->GettechniqeCount() <= 1) {
		NewGO<AIEditNode>(0, "firstwin");
		Choice0 = true;
		fonttarget = true;
	}

	//3つ目のノードは絶対に技なのでそのための処理(ターゲットから技に飛ぶ)。
	if (m_aieditnodeprocess->GettechniqeCount() > 1) {
		m_aieditnodeprocess->Technique();
		m_aieditnodeprocess->Setkeeonode(AIEditNode::enTechnique);
		Choice0 = true;
		fonttarget = true;
	}
}

void AIEditNodeTarget::Technique()
{

	if (Mouse::isTrigger(enLeftClick))	//左クリック
	{
		m_aieditnodetechique = NewGO<AIEditNodeTechnique>(0, "Technique");
		PlayButtonSE();

		Choice0 = true;
	}
}

void AIEditNodeTarget::FontsConfirmation()
{
	CVector2 m_fontpos1 = CVector2::Zero();
	m_fontpos1.x -= 180;
	m_fontpos1.y += 360;
	bool cont = true;

	if (m_nodebuttons[button - 3]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"じぶん", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
		m_font[0]->DrawShadow({ 5,-5 });
			
		contact1 = true;
	}

	else if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"みかた", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
		m_font[0]->DrawShadow({ 5,-5 });

		contact1 = true;
	}
		
	else if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
		m_font[0]->Init(L"てき", { m_fontpos1 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });
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

void AIEditNodeTarget::Update()
{
	cursorpos = m_gamecursor->GetCursor();
	
	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);
	}

	if (contact2 == false) {
		FontsConfirmation();
	}

	if (Choice0 == false) { //何も選択していないとき

		if (Mouse::isTrigger(enLeftClick)) {	//左クリック
			if (m_nodebuttons[button - 3]->GetSpriteRender()->isCollidingTarget()) {
				PlayButtonSE();

				m_target = enme;
				m_aieditnodeprocess->Setkeeptarget(enme);
				Num();
				contact2 = true;
			}

			if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
				m_target = enbaddy;
				m_aieditnodeprocess->Setkeeptarget(enbaddy);
				PlayButtonSE();
				Num();
				contact2 = true;
			}

			if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
				m_target = enenemy;
				m_aieditnodeprocess->Setkeeptarget(enenemy);
				PlayButtonSE();
				Num();
				contact2 = true;
			}
		}
	}
}