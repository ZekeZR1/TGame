//3
#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeOrder.h"
#include "AIEditLine.h"
#include "AIEditNodeButton.h"

AIEditNodeNum::~AIEditNodeNum()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}
}


bool AIEditNodeNum::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(5, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/sieat.dds", 150, 250);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標

	for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
		m_aieditnodebutton = NewGO<AIEditNodeButton>(6, "button");
		m_aieditnodebutton->SetPri(6);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}
	return true;
}


void AIEditNodeNum::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}
	
	for (int i = 0; i < button; i++)
	{
		if (Choice3 == false) {
			if (m_nodebuttons[i]->GetSpriteRender()->isCollidingTarget())
			{
				Order();
			}
		}
	}

}

void AIEditNodeNum::Order()
{

	if (Mouse::isTrigger(enLeftClick)) {	//左クリック
		m_aieditnodeorder = NewGO<AIEditNodeOrder>(0, "Order");
		Choice3 = true;
	}
}
