#include "stdafx.h"
#include "AIEditNode.h"

#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"

#include "AIEditNodeHp.h"


AIEditNode::~AIEditNode()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_spriteRender1);
	DeleteGO(m_spriteRender2);
	DeleteGO(m_spriteRender3);
	DeleteGO(m_spriteRender4);
	DeleteGO(m_spriteRender5);
}



bool AIEditNode::Start()
{

	m_gamecursor = FindGO<GameCursor>("cursor");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(3, "firstwin");
	m_spriteRender->Init(L"Assets/sprite/winkari.dds", 300, 500);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);			//カーソルの座標

	//ボタン１～
	SetPointPos(-70, 140);
	m_spriteRender1= NewGO<SpriteRender>(2, "miniwin1");
	m_spriteRender1->Init(L"Assets/sprite/Hp.dds", 140, 100, true);
	m_spriteRender1->SetPosition(m_pointposition);

	SetPointPos(70, 140);
	m_spriteRender2 = NewGO<SpriteRender>(2, "miniwin2");
	m_spriteRender2->Init(L"Assets/sprite/Mp.dds", 140, 100, true);
	m_spriteRender2->SetPosition(m_pointposition);

	SetPointPos(-70, 40);
	m_spriteRender3 = NewGO<SpriteRender>(2, "miniwin3");
	m_spriteRender3->Init(L"Assets/sprite/karipoint.dds", 140, 100, true);
	m_spriteRender3->SetPosition(m_pointposition);

	SetPointPos(70, 40);
	m_spriteRender4 = NewGO<SpriteRender>(2, "miniwin4");
	m_spriteRender4->Init(L"Assets/sprite/karipoint.dds", 140, 100, true);
	m_spriteRender4->SetPosition(m_pointposition);

	SetPointPos(-70, -40);
	m_spriteRender5 = NewGO<SpriteRender>(2, "miniwin5");
	m_spriteRender5->Init(L"Assets/sprite/karipoint.dds", 140, 100, true);
	m_spriteRender5->SetPosition(m_pointposition);

	return true;

}

//選択ボタンの手打ち補助
void AIEditNode::SetPointPos(int numx, int numy)
{
	//仮の値
	float x = 0;
	float y = 0;
	x = m_position.x;
	y = m_position.y;
	m_pointposition.x = x + numx;
	m_pointposition.y = y + numy;

}

//void AIEditNode::PostReider(CRenderContext & rc)
//{
//
//
//
//}


void AIEditNode::Update()
{
	CVector3 cursorpos = m_gamecursor->GetCursor();

	m_spriteRender1->SetCollisionTarget(cursorpos);


		if (m_spriteRender1->isCollidingTarget())	//Hpを選択しているか	
		{

			if (Mouse::isTrigger(enLeftClick))	//右クリック
				NewGO<AIEditNodeHp>(0, "Hp");

		}
	
	
}

