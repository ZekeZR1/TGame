#include "stdafx.h"
#include "AIEditNodeClick.h"
#include "AIEditNode.h"
#include "AIEditLine.h"
#include "../GameCursor.h"

//camera
#include "../../GameCamera.h"

AIEditNodeClick::~AIEditNodeClick()
{
	DeleteGO(m_spriteRender);

}


bool AIEditNodeClick::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");

	m_position.x = x;
	m_position.y = y;
	m_spriteRender = NewGO<SpriteRender>(0, "mass");
	m_spriteRender->Init(L"Assets/sprite/click.dds", 250, 150,true); //last
	m_spriteRender->SetPosition(m_position);

	return true;

}


void AIEditNodeClick::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	m_spriteRender->SetCollisionTarget(cursorpos);

	if (Choice0 == false) {

		if (Mouse::isTrigger(enLeftClick)) {

			if (m_spriteRender->isCollidingTarget()) {

				m_aieditnode = NewGO<AIEditNode>(0, "window");

				Choice0 = true;
			}

		}
	}
}
