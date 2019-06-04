#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeDeleteKey.h"
#include "AIEditNodeOrder.h"
#include "AIEditLine.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeTechnique.h"

AIEditNodeDeleteKey::~AIEditNodeDeleteKey()
{
}

void AIEditNodeDeleteKey::OnDestroy()
{
	DeleteGO(m_spriteRender);
}


bool AIEditNodeDeleteKey::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	//m_aieditnodeorder = FindGO<AIEditNodeOrder>("order");
	m_aieditline = FindGO<AIEditLine>("Line");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_aieditnodetechnique = FindGO<AIEditNodeTechnique>("techniqu");

	//一番新しいorderの座標を調べる。
	CVector3 v = CVector3::Zero();
	QueryGOs<AIEditNodeOrder>("order", [&](auto go)->bool
	{
		v = go->GetPos();
		return true;
	});
	m_position = m_orderpoint->GetPos();
	
	m_spriteRender = NewGO<SpriteRender>(3, "delete");
	m_spriteRender->Init(L"Assets/sprite/deletepoint.dds", 25, 25, true);
	m_position.x += 160;
	m_spriteRender->SetPosition(m_position);


	return true;
}

void AIEditNodeDeleteKey::SetOrder(AIEditNodeOrder* a)
{
	m_orderpoint = a;

}

void AIEditNodeDeleteKey::deleteclick()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();
	m_spriteRender->SetCollisionTarget(cursorpos);

	if (Mouse::isTrigger(enLeftClick)) {
		if (m_spriteRender->isCollidingTarget())
		{
			PlayButtonSE();

			//列すべてのものをDelete。
			m_aieditnodeprocess->DeleteKey(m_orderpoint);
			m_aieditnodeprocess->Click();
			//m_aieditnodeprocess->SetTechniqueGenerate(false);
		}
	}
}

void AIEditNodeDeleteKey::Update() 
{

	if (m_aieditnodeprocess->GetTechniqueGenerate() == true) {
		deleteclick();
		
	}

}