#include "stdafx.h"
#include "AIEditNode.h"

#include "../GameCursor.h"

// THIS IS CAMERA.
#include "../../GameCamera.h"



AIEditNode::~AIEditNode()
{

}



bool AIEditNode::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(0, "firstwin");
	m_spriteRender->Init(L"sprite/winkari.dds", 300, 500);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);			//カーソルの座標

	//ボタン１～
	SetPointPos(0, 0);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin1");
	m_spriteRender->Init(L"sprite/pointkari.dds", 100, 100);
	m_spriteRender->SetPosition(m_pointposition);

	SetPointPos(50, 50);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin2");
	m_spriteRender->Init(L"sprite/pointkari.dds", 100, 100);
	m_spriteRender->SetPosition(m_pointposition);

	SetPointPos(50, 100);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin3");
	m_spriteRender->Init(L"sprite/pointkari.dds", 100, 100);
	m_spriteRender->SetPosition(m_pointposition);

	SetPointPos(100, 50);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin4");
	m_spriteRender->Init(L"sprite/pointkari.dds", 100, 100);
	m_spriteRender->SetPosition(m_pointposition);

	SetPointPos(100, 100);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin5");
	m_spriteRender->Init(L"sprite/pointkari.dds", 100, 100);
	m_spriteRender->SetPosition(m_pointposition);

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

void AIEditNode::Update()
{


	
}

