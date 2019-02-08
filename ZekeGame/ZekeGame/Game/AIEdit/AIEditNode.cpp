//1
#include "stdafx.h"
#include "AIEditNode.h"

#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"

#include "AIEditNodeHp.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeButton.h"
#include "AIEditNodeTechnique.h"
#include "AIEdtiNodeAbnormalState.h"

AIEditNode::~AIEditNode()
{
	DeleteGO(m_spriteRender);
	for (AIEditNodeButton* sp : m_nodebuttons)
	{
		DeleteGO(sp);
	}

}



bool AIEditNode::Start()
{

	m_gamecursor = FindGO<GameCursor>("cursor");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(1, "firstwin");
	m_spriteRender->Init(L"Assets/sprite/sieat.dds", 150, 250);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);			//カーソルの座標
	
	////ボタン専用
	//for (int i = 0; i < button; i++)		//iは数を回すだけのハム太郎  
	//{
	//	x *= -1;					
	//	if (i % 2 == 0)
	//	{
	//		y -= 50;
	//	}
	//	SetPointPos(x,y);
	//	sr = NewGO<SpriteRender>(2, "miniwin");
	//	sr->Init(L"Assets/sprite/karipoint.dds", 70, 50, true);
	//	sr->SetPosition(m_pointposition);
	//	m_spriteRenders.push_back(sr);
	//	
	//}
	

	//改造中
	for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
		m_aieditnodebutton = NewGO<AIEditNodeButton>(2, "button");
		m_aieditnodebutton->SetPri(2);
		m_aieditnodebutton->SetButton(i + 1);
		m_aieditnodebutton->SetPos(m_position);
		m_nodebuttons.push_back(m_aieditnodebutton);
	}
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
		NewGO<AIEditNodeTechnique>(0, "Technique");

		Choice1 = true;
	}

}

void AIEditNode::Abnormal()
{

	if (Mouse::isTrigger(enLeftClick))	//左クリック
	{
		NewGO<AIEditNodeAbnormalState>(0, "Abnormal");

		Choice1 = true;
	}

}

void AIEditNode::Update()
{
	CVector3 cursorpos = m_gamecursor->GetCursor();
	 
	for (int i = 0; i < button; i++) {
		SpriteRender* sp = m_nodebuttons[i]->GetSpriteRender();
		sp->SetCollisionTarget(cursorpos);

	}

	if (Choice1 == false) { //何も選択していないとき

		for (int i = 0; i < button - 2; i++) {
			if (m_nodebuttons[i]->GetSpriteRender()->isCollidingTarget())	//選択しているか	
			{
				Inequ();
			
			}
			
		}

		if (m_nodebuttons[button - 2]->GetSpriteRender()->isCollidingTarget()) {

			Abnormal();
		}

		if (m_nodebuttons[button - 1]->GetSpriteRender()->isCollidingTarget()) {

			Technique();
		}
	}
	
}

