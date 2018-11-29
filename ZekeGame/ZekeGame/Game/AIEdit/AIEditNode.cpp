#include "stdafx.h"
#include "AIEditNode.h"

#include "../GameCursor.h"

#include "../../GameCamera.h"

AIEditNode::~AIEditNode()
{

}


bool AIEditNode::Start()
{
	//window•\Ž¦J
	m_spriteRender = NewGO<SpriteRender>(0, "window");
	//m_spriteRender->Init(L"sprite/kariwindow.dds", 1300, 750);
	m_spriteRender->Init(L"Assets/Sprite/kariwindow.dds", 500, 500);
	//m_spriteRender->SetPosition("mausu");
	m_spriteRender->SetPosition(CVector3::Zero());
	return true;
}


void AIEditNode::Update()
{
	

}