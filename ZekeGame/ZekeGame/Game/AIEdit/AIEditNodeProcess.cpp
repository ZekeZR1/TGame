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
#include "AIEditNodeMenu.h"
#include "../GameCursor.h"
#include "AIEditNodeSelectButtons.h"
#include "AIEditNodeDeleteKey.h"

//camera
#include "../../GameCamera.h"


AIEditNodeProcess::~AIEditNodeProcess()
{

}

bool AIEditNodeProcess::Start()
{

	m_aieditnodeclick = FindGO<AIEditNodeClick>("click");
	m_aieditnodeorder = FindGO<AIEditNodeOrder>("order");

	if (num <= 7) {
		Click();
	}
	//m_aieditnodemenu = NewGO<AIEditNodeMenu>(0, "menu");
	m_aieditnodeselectbuttons = NewGO<AIEditNodeSelectButtons>(0, "selectbuttons");


	//すべてのflagkeepにnullを代入しておく。
	for (int i = 0; i <= 7; i++) {

		for (int j = 0; j <= 1; j++) {

			for (int k = 0; k <= 4; k++) {

				flagkeep[i][j][k] = 0;            //0は何も選択していない状態。(nulptr)

			}
		}
	}

	for (int i = 0; i <= 7; i++) {

		for (int j = 0; j <= 2; j++) {
			m_orderkeep[i][j] = nullptr;
		}
	}
	
	return true;
}



void AIEditNodeProcess::Click()
{
	//clickが出ていたらDeleteする。
	QueryGOs<AIEditNodeClick>("click",[&](auto* go)->bool
	{
		DeleteGO(go);
		num -= 1;             //Clickの条件を調整する。
		return true;
	});

	//8個までしか出ないようにする。
	if (num <= 7) {
		/*m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");*/

		for (int i = 0; i <= 7; i++) {

			m_orderkeep[i][0];

			if (m_orderkeep[i][0] == nullptr) {

				m_aieditnodeclick = NewGO<AIEditNodeClick>(0, "click");
				float y = ClickePosY - 85 * i;
				m_aieditnodeclick->SetPosition({ -430,y,0 });
				break;
			}
		}

		num += 1;

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

void AIEditNodeProcess::DeleteKey(AIEditNodeOrder* a)
{
	bool isBreak = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			if (m_orderkeep[i][j] == a) {
				//orderをDeleteする。
				DeleteGO(m_orderkeep[i][0]);
				DeleteGO(m_orderkeep[i][1]);
				DeleteGO(m_orderkeep[i][2]);
				m_orderkeep[i][0] = nullptr;
				m_orderkeep[i][1] = nullptr;
				m_orderkeep[i][2] = nullptr;
				////deletekeyをDeleteする。
				//DeleteGO(m_aieditnodedeletekey);
				isBreak = true;

				break;
			}
		}
		if (isBreak == true)
			break;

	}
}

//orderの状態を保持する。
AIEditNodeOrder * AIEditNodeProcess::CreateOrder()
{

	m_aieditnodeorder = NewGO<AIEditNodeOrder>(0,"order");
	bool flaflag = false;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
		
			if (m_orderkeep[i][j] == nullptr) {
				m_orderkeep[i][j] = m_aieditnodeorder;
				flaflag = true;
				break;
			}

			else if (j<2 && m_orderkeep[i][j]->GettechniqueOrder() == true) {
				if (m_orderkeep[i + 1][0] == nullptr)
				{
					m_orderkeep[i + 1][0] = m_aieditnodeorder;
					flaflag = true;
				}
				break;
			}
		}

		if (flaflag == true) {
			break;
		}
	}

	return m_aieditnodeorder;
}

void AIEditNodeProcess::AISave()
{
	FILE* f = fopen("Assets/VisualAI/AISave.va","w");
	
	for (int i0 = 0;i0 < 8; i0++)
	{
		for (int i1 = 0;i1 < 3;i1++)
		{
			for (int i2 = 0; i2 < 6; i2++)
			{
				fwrite(&flagkeep[i0][i1][i2], 2, 1, f);
			}
		}
	}
	fclose(f);
}

void AIEditNodeProcess::Update()
{
		


}
