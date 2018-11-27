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

	return true;

}



void AIEditNode::Update()
{

	if ("マウス右クリック")
	{
		m_spriteRender = NewGO<SpriteRender>(0,"firstwin");
		m_spriteRender->Init(L"sprite/kariwin.dds", 700, 400);


	}

}