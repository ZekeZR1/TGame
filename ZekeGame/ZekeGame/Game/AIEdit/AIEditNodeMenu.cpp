#include "stdafx.h"
#include "AIEditNodeMenu.h"
#include "../GameCursor.h"
#include "AIEditMode.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeButton.h"
#include "AIEditLine.h"
#include "AIEditNode.h"
#include "AIEditNodeClick.h"
#include "AIEditNodeInequ.h"
#include "AIEditNodeMass.h"
#include "AIEditNodeNum.h"
#include "AIEditNodeOrder.h"
#include "AIEditNodeTarget.h"
#include "AIEditNodeTechnique.h"
#include "AIEdtiNodeAbnormalState.h"
//#include "AIeditModeSelect.h"

AIEditNodeMenu::~AIEditNodeMenu()
{
	DeleteGO(m_spriteRender);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
}


bool AIEditNodeMenu::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodebutton = FindGO<AIEditNodeButton>("button");


	return true;
}

void AIEditNodeMenu::BackMenu()
{
	/*if (m_aieditline != nullptr) {
		DeleteGO(m_aieditline);
		m_aieditline = nullptr;
	}

	if (m_aieditnode != nullptr) {
		DeleteGO(m_aieditnode);
		m_aieditnode = nullptr;
	}

	if (m_aieditnodeabnormalstate != nullptr) {
		DeleteGO(m_aieditnodeabnormalstate);
		m_aieditnodeabnormalstate = nullptr;
	}

	if (m_aieditnodebutton != nullptr) {
		DeleteGO(m_aieditnodebutton);
		m_aieditnodebutton = nullptr;
	}

	if (m_aieditnodeclick != nullptr) {
		DeleteGO(m_aieditnodeclick);
		m_aieditnodeclick = nullptr;
	}

	if (m_aieditnodeinequ != nullptr) {
		DeleteGO(m_aieditnodeinequ);
		m_aieditnodeinequ = nullptr;
	}

	if (m_aieditnodemass != nullptr) {
		DeleteGO(m_aieditnodemass);
		m_aieditnodemass = nullptr;
	}

	if (m_aieditnodenum != nullptr) {
		DeleteGO(m_aieditnodenum);
		m_aieditnodenum = nullptr;
	}

	if (m_aieditnodeorder != nullptr) {
		DeleteGO(m_aieditnodeorder);
		m_aieditnodeorder = nullptr;
	}

	if (m_aieditnodeprocess != nullptr) {
		DeleteGO(m_aieditnodeprocess);
		m_aieditnodeprocess = nullptr;
	}

	if (m_aieditnodetarget != nullptr) {
		DeleteGO(m_aieditnodetarget);
		m_aieditnodetarget = nullptr;
	}

	if (m_aieditnodetechnique != nullptr) {
		DeleteGO(m_aieditnodetechnique);
		m_aieditnodetechnique = nullptr;
	}*/

	QueryGOs<AIEditLine>("line", [&](AIEditLine* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditMode>("Mode", [&](AIEditMode* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNode>("firstwin", [&](AIEditNode* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeAbnormalState>("abnormal", [&](AIEditNodeAbnormalState* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeButton>("button", [&](AIEditNodeButton* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeClick>("click", [&](AIEditNodeClick* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeInequ>("lnequ", [&](AIEditNodeInequ* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeMass>("mass", [&](AIEditNodeMass* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeNum>("num", [&](AIEditNodeNum* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeOrder>("order", [&](AIEditNodeOrder* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeProcess>("process", [&](AIEditNodeProcess* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeTarget>("target", [&](AIEditNodeTarget* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeTechnique>("Technique", [&](AIEditNodeTechnique* go)->bool
	{
		DeleteGO(go);
		return true;
	});


	DeleteGO(this);
}

void AIEditNodeMenu::Update()
{
	CVector3 cursorpos = m_gamecursor->GetCursor();

	if (Mouse::isTrigger(enRightClick)) {	//右クリック
		if (menu == false) {
			m_spriteRender = NewGO<SpriteRender>(15, "menu");
			m_spriteRender->Init(L"Assets/sprite/menu.dds", 400, 400, true);
			m_spriteRender->SetPosition(m_position);

			//for (int i = 0; i < button; i++) {               //ボタンの数分ループする。
			//	m_aieditnodebutton = NewGO<AIEditNodeButton>(16, "button ");
			//	m_aieditnodebutton->SetPri(16);
			//	m_aieditnodebutton->SetButton(i + 1);
			//	m_aieditnodebutton->SetPos(m_position);
			//	m_nodebuttons.push_back(m_aieditnodebutton);
			//}

			for (int i = 0; i < button; i++) {
				m_fonts.push_back(NewGO<FontRender>(17));
			}
			//auto bacon = m_nodebuttons[0]->GetPos();
			CVector2 m_fontpos = CVector2::Zero();
			m_fontpos.x -= 150;
			m_fontpos.y += 30;
			m_fonts[0]->Init(L"メニューへ戻る", { m_fontpos }, 0.0, CVector4::Red, 1.0, { 0.0,0.0 });
			menu = true;
		}
	}
	if (menu == true) {
		if (Mouse::isTrigger(enLeftClick)) {	//左クリック
			m_spriteRender->SetCollisionTarget(cursorpos);
			if (m_spriteRender->isCollidingTarget())
			{
				BackMenu();
			}
		}
	}
	
}
