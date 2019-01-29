//4
#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeClick.h"
#include "AIEditLine.h"
#include "../GameCursor.h"

#include "AIEditNodeOrder.h"
AIEditNodeOrder::~AIEditNodeOrder()
{
	DeleteGO(m_spriteRender);

}

bool AIEditNodeOrder::Start()
{

	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeclick = FindGO<AIEditNodeClick>("firstbutton");
	m_aieditnode = FindGO<AIEditNode>("window");
	m_aieditnodeinequ = FindGO<AIEditNodeInequ>("Inequality");
	m_aieditnodenum = FindGO<AIEditNodeNum>("Num");
	m_aieditline = FindGO<AIEditLine>("Line");

	m_aieditline = NewGO<AIEditLine>(0, "Line");

	//if (Click == false) {
	//	m_pos = m_aieditnodeclick->GetPosition();
	//}

	//if (Click == true) {
	//	m_pos = m_aieditnodetriangle->GetPos();
	//}

	//m_pos.x += 30;
	//m_spriteRender = NewGO<SpriteRender>(8, "mass");
	//m_spriteRender->Init(L"Assets/sprite/masss.dds", 300, 120);  //last
	//m_spriteRender->SetPosition(m_pos);

	//各フラグをリセットする。

	//m_aieditnodeclick->GetChoice0(false);

	//大事よ
	/*m_aieditnode->SetChoice1(false);
	m_aieditnodeinequ->GetChoice2(false);
	m_aieditnodenum->GetChoice3(false);*/

	//DeleteGO(m_aieditnode);
	//DeleteGO(m_aieditnodeinequ);
	//DeleteGO(m_aieditnodenum);
	//if (Click == false) {
	//	DeleteGO(m_aieditnodeclick);
	//	Click = true;
	//}
	return true;

}


void AIEditNodeOrder::Update()
{

	//if (Click == false) {
		m_pos = m_aieditnodeclick->GetPosition();
	//}

	//if (Click == true) {
	//	m_pos = m_aieditline->GetPos();
	//}

	m_pos.x += 30;
	m_spriteRender = NewGO<SpriteRender>(8, "mass");
	m_spriteRender->Init(L"Assets/sprite/masss.dds", 300, 120);  //last
	m_spriteRender->SetPosition(m_pos);

	if (Click == false) {
	DeleteGO(m_aieditnode);
	DeleteGO(m_aieditnodeinequ);
	DeleteGO(m_aieditnodenum);
	DeleteGO(m_aieditnodeclick);
	Click = true;
	}

}