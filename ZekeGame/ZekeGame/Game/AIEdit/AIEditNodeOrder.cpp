//4
#include "stdafx.h"
#include "AIEditMode.h"
#include "AIEditNode.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeClick.h"
#include "AIEditLine.h"
#include "AIEditNodeTarget.h"
#include "../GameCursor.h"

#include "AIEditNodeOrder.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeTechnique.h"
#include "AIEdtiNodeAbnormalState.h"
AIEditNodeOrder::~AIEditNodeOrder()
{
	DeleteGO(m_spriteRender);

}

bool AIEditNodeOrder::Start()
{
	static bool Click = 0;

	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeclick = FindGO<AIEditNodeClick>("click");
	m_aieditnode = FindGO<AIEditNode>("firstwin");
	m_aieditnodeinequ = FindGO<AIEditNodeInequ>("Inequality");
	m_aieditnodenum = FindGO<AIEditNodeNum>("Num");
	m_aieditnodetarget = FindGO<AIEditNodeTarget>("target");
	m_aieditline = FindGO<AIEditLine>("Line");
	m_aieditnodeabnormalstate = FindGO<AIEditNodeAbnormalState>("Abnormal");
	m_aieditnodetechnique = FindGO<AIEditNodeTechnique>("Technique");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	
	CVector3 v = CVector3::Zero();
	QueryGOs<AIEditLine>("Line", [&](auto go)->bool
	{
		v = go->GetPos();
		return true;
	});
	m_pos = v;

	m_pos.x += 300;

	if (Click == false) {                                   //Clickがあるとき。
		m_pos = m_aieditnodeclick->GetPosition();
		m_pos.x += 30;
	}


	m_spriteRender = NewGO<SpriteRender>(8, "mass");
	m_spriteRender->Init(L"Assets/sprite/masss.dds", 300, 120);  //last
	m_spriteRender->SetPosition(m_pos);
	Click = true;

	//技を選択したら出ないようにする。
	if(Technique == false){
		m_aieditline = NewGO<AIEditLine>(0, "Line");
		m_aieditline->SetPos(m_pos);
	}


	if (m_aieditnodetarget != nullptr) {
		DeleteGO(m_aieditnodetarget);
		m_aieditnodetarget = nullptr;
	}

	if (m_aieditnode != nullptr) {
		DeleteGO(m_aieditnode);
		m_aieditnode = nullptr;
	}

	if (m_aieditnodeinequ != nullptr) {
		DeleteGO(m_aieditnodeinequ);
		m_aieditnodeinequ = nullptr;
	}

	if (m_aieditnodenum != nullptr) {
		DeleteGO(m_aieditnodenum);
		m_aieditnodenum = nullptr;
	}

	if (m_aieditnodeclick != nullptr) {
		DeleteGO(m_aieditnodeclick);
		m_aieditnodeclick = nullptr;
	}

	if (m_aieditnodeabnormalstate != nullptr) {
		DeleteGO(m_aieditnodeabnormalstate);
		m_aieditnodeabnormalstate = nullptr;
	}

	if (m_aieditnodetechnique != nullptr) {
		DeleteGO(m_aieditnodetechnique);
		m_aieditnodetechnique = nullptr;
		//Clickを表示する。
		m_aieditnodeprocess->enSecond();
		m_aieditnodeprocess = NewGO<AIEditNodeProcess>(0, "process");
	}

	return true;

}


void AIEditNodeOrder::Update()
{


}