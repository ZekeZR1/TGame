//一連の処理だお
#include "stdafx.h"

#include "AIEditNode.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeNum.h"

#include "AIEditNodeProcess.h"
#include "AIEditLine.h"
#include "AIEditNodeOrder.h"
#include "AIEditLine.h"
#include "AIEditNodeTarget.h"
#include "AIEditNodeClick.h"
#include "../GameCursor.h"

//camera
#include "../../GameCamera.h"


AIEditNodeProcess::~AIEditNodeProcess()
{

}



bool AIEditNodeProcess::Start()
{
	State state;


	
	return true;
}


void AIEditNodeProcess::Update()
{
	if (NewChoice1 == false) {

		m_spriteRender = NewGO<SpriteRender>(0, "win");
		m_spriteRender->Init(L"Assets/sprite/haik.dds", 1280, 720);
		m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "firstbutton");

		NewChoice1 = true;
	}

	/*if (NewChoice1 == false) {
		m_aieditnode = NewGO<AIEditNode>(0, "window");
		NewChoice1 = true;
	}


	if (NewChoice1 = true) {
		if (NewChoice2 == false) {
			m_aieditnodeinequ = NewGO<AIEditNodeInequ>(0, "Inequality");
			NewChoice2 = true;
		}
	}


	if (NewChoice2 = true) {
		if (NewChoice3 == false) {
			m_aieditnodenum = NewGO<AIEditNodeNum>(0, "Num");
			NewChoice3 = true;
		}
	}


	if (NewChoice3 = true) {
		if (OrderChoice = false) {
			m_aieditnodeorder = NewGO<AIEditNodeOrder>(0,"Order");
			m_aieditline = NewGO<AIEditLine>(0, "Line");
			OrderChoice = true;
		}

	}*/

}

//シートの座標指定？
//何で作ったか忘れた
void AIEditNodeProcess::ButtonPosition()
{



}