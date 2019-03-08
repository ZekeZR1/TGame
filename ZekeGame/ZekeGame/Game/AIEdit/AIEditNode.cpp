//1
#include "stdafx.h"
#include "AIEditNode.h"

#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeTechnique.h"
#include "AIEdtiNodeAbnormalState.h"
#include "AIEditNodeProcess.h"

AIEditNode::~AIEditNode()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}



bool AIEditNode::Start()
{

	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(6, "firstwin");
	m_spriteRender->Init(L"Assets/sprite/menu2.dds", 175, 280);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);			//カーソルの座標


	//ぼたん。
	for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
		m_aieditnodebutton = NewGO<AIEditNodeButton>(7, "button");
		m_aieditnodebutton->SetPri(7);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}

	//フォント。
	for (int i = 0; i < button; i++) {
		m_fonts.push_back(NewGO<FontRender>(8));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}

	auto bacon = m_nodebuttons[0]->GetPos();

	CVector2 m_fontpos = CVector2::Zero();
	m_fontpos.x = bacon.x - 50.0;
	m_fontpos.y = bacon.y + 110.0;
	m_fonts[0]->Init(L" HP", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.y -= 57.f;
	m_fonts[1]->Init(L" MP", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x -= 14.f;
	m_fontpos.y -= 63.f;
	m_fonts[2]->Init(L"状態異常", { m_fontpos }, 0.0, CVector4::White, 0.7, { 0.0,0.0 });
	m_fontpos.x += 14.f;
	m_fontpos.y -= 45.f;
	m_fonts[3]->Init(L" 技", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });

	return true;

}


void AIEditNode::Inequ()
{
	if (Mouse::isTrigger(enLeftClick))	//左クリック
	{
		NewGO<AIEditNodeInequ>(0, "Inequality");
			
		Choice1 = true;
	}

}

void AIEditNode::Technique()
{

	if (Mouse::isTrigger(enLeftClick))	//左クリック
	{
		//NewGO<AIEditNodeTechnique>(0, "Technique");
		m_aieditnodeprocess->Technique();
		Choice1 = true;
	}

}

void AIEditNode::Abnormal()
{

		NewGO<AIEditNodeAbnormalState>(0, "Abnormal");

		Choice1 = true;
	

}

void AIEditNode::Update()
{
	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}
	if (Choice1 == false) {
		if (Mouse::isTrigger(enLeftClick)) {	//左クリック
			if (m_nodebuttons[button - 4]->GetSpriteRender()->isCollidingTarget()) {
				m_Node = enHp;
				m_aieditnodeprocess->Setkeeonode(enHp);
				Inequ();
			}

			if (m_nodebuttons[button - 3]->GetSpriteRender()->isCollidingTarget()) {
				m_Node = enMp;
				m_aieditnodeprocess->Setkeeonode(enMp);
				Inequ();
			}

			if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {
				m_Node = enAb;
				m_aieditnodeprocess->Setkeeonode(enAb);
				Abnormal();
			}

			if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {
				m_Node = enTechnique;
				m_aieditnodeprocess->Setkeeonode(enTechnique);
				Technique();
			}
		}
	}

}
	