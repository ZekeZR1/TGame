//Clickを生成するクラス
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
	m_aieditnodeclick = FindGO<AIEditNodeClick>("click");
	State state;

	//todo 別クラスからStateが変更できるなら書き換える。
	//if(StateNum == 1) {
	//	m_state = enFirstOrder;
	//}

	//if (StateNum == 2) {
	//	m_state = enSecondOrder;
	//}

	//if (StateNum == 3) {
	//	m_state = enThirdOrder;
	//}

	//if(StateNum == 4) {
	//	m_state = enFourthOrder;
	//}

	//if (StateNum == 5) {
	//	m_state = enFifthOrder;
	//}

	//if (StateNum == 6) {
	//	m_state = enSixthOrder;
	//}

	//if (StateNum == 7) {
	//	m_state = enSeventhOrder;
	//}

	//if (m_state == 8) {
	//	m_state = enEighthOrder;
	//}

	
	return true;
}


void AIEditNodeProcess::Update()
{
	switch (m_state) {
	case enFirstOrder:
		if (Choice1 == false) {
			m_spriteRender = NewGO<SpriteRender>(0, "win");
			m_spriteRender->Init(L"Assets/sprite/haik.dds", 1280, 720);
			
			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			/*m_aieditnodeclick->SetPosy(288);*/
			Choice1 = true;

		}
	
		break;

	case enSecondOrder:

		if (Choice2 == false) {

			/*m_aieditnodeclick->SetPosy(200);*/
			y = 200;
			m_aieditnodeclick->SetPro(true);
			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			
			Choice2 = true;

		}

		break;

	case enThirdOrder:

		if (Choice3 == false) {

			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			Choice3 = true;

		}

		break;

	case enFourthOrder:

		if (Choice4 == false) {

			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			Choice4 = true;

		}

		break;

	case enFifthOrder:

		if (Choice5 == false) {

			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			Choice5 = true;

		}

		break;

	case enSixthOrder:

		if (Choice6 == false) {

			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			Choice6 = true;

		}

		break;

	case enSeventhOrder:

		if (Choice7 == false) {

			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			Choice7 = true;

		}
		break;

	case enEighthOrder:

		if (Choice8 == false) {

			m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
			Choice8 = true;

		}

		break;
	}
}

//シートの座標指定？
//何で作ったか忘れた
void AIEditNodeProcess::ButtonPosition()
{



}