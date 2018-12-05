#include "stdafx.h"
#include "AIEditNodeHp.h"

#include "../GameCursor.h"

#include "../../GameCamera.h"

#include "AIEditNode.h"


AIEditNodeHp::~AIEditNodeHp()
{

	DeleteGO(m_spriteRender);
}


bool AIEditNodeHp::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	//m_aieditnode = FindGO<AIEditNode>("firstwin");

	//UIの基盤
	m_spriteRender = NewGO<SpriteRender>(1, "firstwinhp");
	m_spriteRender->Init(L"Assets/sprite/winkari.dds", 300, 500);
	CVector3 cursorpos = m_gamecursor->GetCursor();
	cursorpos.x += 270.0f;
	cursorpos.y += -140.0f;
	m_position = cursorpos;
	m_spriteRender->SetPosition(m_position);	//AIEditNodeのボタンの座標座標
	/*CVector3 kaku = m_aieditnode->m_position;
	m_spriteRender->SetPosition(m_position);	*/		


	SetPointPos(-70, 140);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin1");
	m_spriteRender->Init(L"Assets/sprite/karipoint.dds", 140, 100);
	m_spriteRender->SetPosition(m_pointposition);

	SetPointPos(70, 140);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin2");
	m_spriteRender->Init(L"Assets/sprite/karipoint.dds", 140, 100);
	m_spriteRender->SetPosition(m_pointposition);

	SetPointPos(-70, 40);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin3");
	m_spriteRender->Init(L"Assets/sprite/karipoint.dds", 140, 100);
	m_spriteRender->SetPosition(m_pointposition);

	SetPointPos(70, 40);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin4");
	m_spriteRender->Init(L"Assets/sprite/karipoint.dds", 140, 100);
	m_spriteRender->SetPosition(m_pointposition);

	SetPointPos(0, 200);
	m_spriteRender = NewGO<SpriteRender>(0, "miniwin5");
	m_spriteRender->Init(L"Assets/sprite/karipoint.dds", 140, 100);
	m_spriteRender->SetPosition(m_pointposition);

	return true;
}



//選択ボタンの手打ち補助
void AIEditNodeHp::SetPointPos(int numx, int numy)
{
	//仮の値
	float x = 0;
	float y = 0;
	x = m_position.x;
	y = m_position.y;
	m_pointposition.x = x + numx;
	m_pointposition.y = y + numy;

}



void AIEditNodeHp::Update()
{

}