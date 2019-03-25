#include "stdafx.h"
#include "AIEditLine.h"
#include "AIEditNodeOrder.h"
#include "AIEditNode.h"
#include "../GameCursor.h"
#include "AIEditNodeTarget.h"
#include "AIEditNodeProcess.h"
#include"AIEditNodeSelectFonts.h"

//camera
#include "../../GameCamera.h"
AIEditLine::~AIEditLine()
{
	DeleteGO(m_spriteRender);
}

bool AIEditLine::Start()
{
	m_aieditnode = FindGO<AIEditNode>("window");
	m_aieditnodeorder = FindGO<AIEditNodeOrder>("Order");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_spriteRender = NewGO<SpriteRender>(1, "line");
	m_spriteRender->Init(L"Assets/sprite/arrow.dds", 1, 250);  //last
	m_pos.x += 120;
	m_spriteRender->SetPosition(m_pos);
	m_spriteRender->SetPivot({ 0.0f, 0.5f });
	return true;
}

void AIEditLine::Update()
{
	if (x <= 180) {

		x += 6.0;

		m_spriteRender->SetScale({x,1,1});

	}
	

	if (x >= 180) {
	
		if (Choice1 == false) {
			
			m_aieditnodeprocess->Target();
			Choice1 = true;

		}

	}
}