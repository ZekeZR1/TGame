//ClickÇê∂ê¨Ç∑ÇÈÉNÉâÉX
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
#include "AIEditNodeMenu.h"
#include "../GameCursor.h"

//camera
#include "../../GameCamera.h"


AIEditNodeProcess::~AIEditNodeProcess()
{

}

bool AIEditNodeProcess::Start()
{

	m_aieditnodeclick = FindGO<AIEditNodeClick>("click");

	if (num <= 7) {
		Click();
	}
	m_aieditnodemenu = NewGO<AIEditNodeMenu>(0, "menu");
	
	return true;
}


void AIEditNodeProcess::Click()
{
	if (num <= 7) {
		m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
		float y = ClickePosY - 85 * num;
		num += 1;
		m_aieditnodeclick->SetPosition({ -430,y,0 });
	}
}

void AIEditNodeProcess::Target()
{

	m_aieditnodetarget = NewGO<AIEditNodeTarget>(0, "target");
	TechniqueCount += 1;

}

void AIEditNodeProcess::Technique()
{

	m_aieditnodetechnique = NewGO<AIEditNodeTechnique>(0, "Technique");
	TechniqueCount = 0;

}

void AIEditNodeProcess::AISave()
{
	FILE* f = fopen("Assets/VisualAI/AISave.va","a");
	
	for (int i0 =0;i0 < 8;i0++)
	{
		for (int i1 = 0;i1 < 3;i1++)
		{
			for (int i2 = 0; i2 < 6; i2++)
			{
				fwrite(&flagkeep[i0][i1][i2], 3, 1, f);
			}
		}
	}
	fclose(f);
}

void AIEditNodeProcess::Update()
{
		


}
