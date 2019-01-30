//àÍòAÇÃèàóùÇæÇ®
#include "stdafx.h"

#include "AIEditNode.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeNum.h"

#include "AIEditNodeProcess.h"
#include "AIEditLine.h"
#include "../GameCursor.h"

//camera
#include "../../GameCamera.h"


AIEditNodeProcess::~AIEditNodeProcess()
{

}



bool AIEditNodeProcess::Start()
{
	
	return true;
}


void AIEditNodeProcess::Update()
{

	if (NewChoice1 == false) {
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


}