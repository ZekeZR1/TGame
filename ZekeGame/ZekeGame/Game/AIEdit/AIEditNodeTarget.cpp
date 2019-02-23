#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"

#include "AIEditNodeTarget.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeTechnique.h"
#include "AIEditNodeProcess.h"
AIEditNodeTarget::~AIEditNodeTarget()
{
	DeleteGO(m_spriteRender);

	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}



bool AIEditNodeTarget::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	m_spriteRender = NewGO<SpriteRender>(3, "target");
	m_spriteRender->Init(L"Assets/sprite/sieat.dds", 150, 190);
	m_spriteRender->SetPivot({ 0.5f, 0.35f });

	//CVector3 cursorpos = m_gamecursor->GetCursor();
	//cursorpos.x += 135.0f;
	//cursorpos.y += -140.0f;
	//m_position = cursorpos;
	m_position.x -= 100;
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
	}
	auto bacon = m_nodebuttons[0]->GetPos();
	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 50.0;
	m_fontpos.y = bacon.y + 110.0;
	m_fonts[0]->Init(L"自分", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[1]->Init(L"味方", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 55.f;
	m_fonts[2]->Init(L" 敵", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });

	return true;
}

void AIEditNodeTarget::Num() 
{
	if (m_aieditnodeprocess->GettechniqeCount() <= 1) {
		NewGO<AIEditNode>(0, "firstwin");

		Choice0 = true;
	}

	if (m_aieditnodeprocess->GettechniqeCount() > 1) {
		m_aieditnodeprocess->Technique();

		Choice0 = true;
	}
}

void AIEditNodeTarget::Technique()
{

	if (Mouse::isTrigger(enLeftClick))	//左クリック
	{
		m_aieditnodetechique = NewGO<AIEditNodeTechnique>(0, "Technique");

		Choice0 = true;

	}

}

void AIEditNodeTarget::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}

	if (Choice0 == false) { //何も選択していないとき

		for (int i = 0; i < button - 1; i++) {
			if (m_nodebuttons[i]->GetSpriteRender()->isCollidingTarget())	//選択しているか	
			{	
				//Num();

			}

		}
		if (Mouse::isTrigger(enLeftClick)) {	//左クリック
			if (m_nodebuttons[button - 3]->GetSpriteRender()->isCollidingTarget()) {
				m_target = enme;
				Num();
			}

			if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
				m_target = enbaddy;
				Num();
			}

			if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
				m_target = enenemy;
				Num();
			}

			//if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {

			//	//Technique();
			//	if (Mouse::isTrigger(enLeftClick)) {	//左クリック
			//		m_aieditnodeprocess->Technique();
			//		m_target = entechnique;
			//		Choice0 = true;
			//	}
			//}
		}
	}
}