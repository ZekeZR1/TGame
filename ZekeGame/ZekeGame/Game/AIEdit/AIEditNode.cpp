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
	
		//一番初めのwindow
		if ("マウス右クリック")
		{
			m_spriteRender = NewGO<SpriteRender>(0, "firstwin");
			m_spriteRender->Init(L"sprite/kariwin.dds", 700, 400);
			m_spriteRender->SetPosition(/*矢印の下*/);

		}

		//線を伸ばす処理をした時に出てくるwindow
		if ()
		{

		}

}