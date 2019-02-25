//5
#include "stdafx.h"
#include "AIEditLine.h"
#include "AIEditNodeOrder.h"
#include "AIEditNode.h"
#include "../GameCursor.h"
#include "AIEditNodeTarget.h"
#include "AIEditNodeProcess.h"

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
	m_spriteRender->Init(L"Assets/sprite/arrow.dds", 20, 250);  //last
	//m_pos = m_aieditnodeorder->GetPos();
	m_pos.x += 120;
	m_spriteRender->SetPosition(m_pos);
	m_spriteRender->SetPivot({ 0.0f, 0.5f });
	return true;
}

void AIEditLine::Update()
{
	if (x <= 180) {
		x += 6;
		//todo ロードが走っているので、激重。SpriteRenderに拡大率を設定できるようになったらそっちにする。
		m_spriteRender->Init(L"Assets/sprite/arrow.dds", x , 200);
		//m_spriteRender->SetScale();
	}
	

	if (x >= 180) {
		//if (m_aieditnode->GetChoice1() == false) {
		if (Choice1 == false) {

			//if (m_aieditnodeprocess->GettechniqeCount() <= 0) {
				m_aieditnodeprocess->Target();
				Choice1 = true;
			//}

		}

	/*	if (Choice1 == false) {

			if (m_aieditnodeprocess->GettechniqeCount() >= 1){
				m_aieditnodeprocess->Technique();
				Choice1 = true;
			}
			
		}*/
	}
}