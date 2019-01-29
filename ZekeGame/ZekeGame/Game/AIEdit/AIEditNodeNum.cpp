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


AIEditNodeNum::~AIEditNodeNum()
{
	DeleteGO(m_spriteRender);
	for (SpriteRender* sp : m_spriteRenders)
	{
		DeleteGO(sp);
	}
}


bool AIEditNodeNum::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(5, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/winkari.dds", 150, 250);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 135.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標

	int x = 35;			//ボタンのX座標
	int y = 180;		//ボタンのY座標

						//ボタン専用
	for (int i = 0; i < button; i++)		//iは数を回すだけのハム太郎 i<x xのところがボタンの数
	{
		x *= -1;

		if (i % 2 == 0)
		{
			y -= 50;

		}

		SetPointPos(x, y);
		sr = NewGO<SpriteRender>(6, "miniwin");
		sr->Init(L"Assets/sprite/karipoint.dds", 70, 50, true);
		sr->SetPosition(m_pointposition);
		m_spriteRenders.push_back(sr);

	}
	return true;
}


void AIEditNodeNum::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {

		m_spriteRenders[i]->SetCollisionTarget(cursorpos);

	}
	
	for (int i = 0; i < button; i++)
	{
		if (Choice3 == false) {
			if (m_spriteRenders[i]->isCollidingTarget())
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
		//m_aieditline = NewGO<AIEditLine>(0, "Line");
		//m_aieditnodetriangle = NewGO<AIEditNodeTriangle>(0, "Triangle");
		Choice3 = true;
	}
}

//選択ボタンの手打ち補助
void AIEditNodeNum::SetPointPos(int numx, int numy)
{
	//仮の値
	float x = 0;
	float y = -20;
	x = m_position.x;
	y = m_position.y;
	m_pointposition.x = x + numx;
	m_pointposition.y = y + numy;

}