#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"

#include "AIEditNodeTarget.h"
#include"AIEditNodeButton.h"
AIEditNodeTarget::~AIEditNodeTarget()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}

}



bool AIEditNodeTarget::Start()
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

	return true;
}



void AIEditNodeTarget::Update()
{



}