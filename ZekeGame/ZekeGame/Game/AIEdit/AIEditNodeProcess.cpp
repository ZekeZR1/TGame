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
#include "AIEditNodeTechnique.h"
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

	if (num <= 7) {
		Click();
	}
	
	return true;
}


void AIEditNodeProcess::Click()
{
	if (num <= 7) {
		m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
		float y = 288 - 40 * num;
		num += 1;
		m_aieditnodeclick->SetPosition({ -446,y,0 });
	}
}

void AIEditNodeProcess::Target()
{
	//if (TechniqueCount <= 1) {
		m_aieditnodetarget = NewGO<AIEditNodeTarget>(0, "target");
		TechniqueCount += 1;
	//}

}

void AIEditNodeProcess::Technique()
{
	//if (TechniqueCount == 2) {
		m_aieditnodetechnique = NewGO<AIEditNodeTechnique>(0, "Technique");
		TechniqueCount = 0;
	//}
}

void AIEditNodeProcess::Update()
{
		


}

//シートの座標指定？
//何で作ったか忘れた
void AIEditNodeProcess::ButtonPosition()
{



}