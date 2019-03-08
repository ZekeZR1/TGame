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
#include "AIEditMode.h"
#include "../Title/ModeSelect.h"

AIEditNodeMenu::~AIEditNodeMenu()
{
	DeleteGO(m_spriteRender);
	//QueryGOs<AIEditNodeMenu>("menuselectsieat", [&](AIEditNodeMenu* menu) {
	//	DeleteGO(menu);
	//	return true;
	//});

	DeleteGO(m_spriterender2);
	DeleteGO(m_spriterender3);
	DeleteGO(m_spriterender4);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	for (auto button : m_buttons)
		DeleteGO(button);
}


bool AIEditNodeMenu::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodebutton = FindGO<AIEditNodeButton>("button");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	m_spriterender2 = NewGO<SpriteRender>(2,"menu");
	m_spriterender2->Init(L"Assets/sprite/menuselect.dds", 80, 40, true);
	m_position2.x += 585;
	//m_position2.y += 338;
	m_position2.y += 300;    //仮
	m_spriterender2->SetPosition(m_position2);

	m_spriterender3 = NewGO<SpriteRender>(2, "menu");
	m_spriterender3->Init(L"Assets/sprite/help.dds", 40, 40, true);
	m_position3.x += 415;
	m_position3.y += 340;
	m_spriterender3->SetPosition(m_position3);

	m_spriterender4 = NewGO<SpriteRender>(2, "menu");
	m_spriterender4->Init(L"Assets/sprite/hozon.dds", 80, 40, true);
	m_position4.x += 500;
	//m_position4.y += 340;
	m_position4.y += 300;  // 仮。
	m_spriterender4->SetPosition(m_position4);

	return true;
}

void AIEditNodeMenu::BackMenu()
{

	QueryGOs<AIEditLine>("Line", [&](AIEditLine* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditMode>("AIEM", [&](AIEditMode* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNode>("firstwin", [&](AIEditNode* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeAbnormalState>("Abnormal", [&](AIEditNodeAbnormalState* go)->bool
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

	QueryGOs<AIEditNodeInequ>("Inequality", [&](AIEditNodeInequ* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeMass>("mass", [&](AIEditNodeMass* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeNum>("Num", [&](AIEditNodeNum* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeOrder>("Order", [&](AIEditNodeOrder* go)->bool
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

	QueryGOs<AIEditNodeProcess>("process", [&](AIEditNodeProcess* go)->bool
	{
		DeleteGO(go);
		return true;
	});

	//セレクトをNewする。
	m_modeselect = NewGO<ModeSelect>(0, "modeselect");

	DeleteGO(this);
}

void AIEditNodeMenu::Menuwin()
{

	if (Mouse::isTrigger(enLeftClick)) {	//左クリック

		if (m_spriterender2->isCollidingTarget()) {

			if (menu == false) {
				m_spriteRender = NewGO<SpriteRender>(15, "menu");
				m_spriteRender->Init(L"Assets/sprite/menu.dds", 400, 400, true);
				m_spriteRender->SetPosition(m_position);
				m_positionselect = m_position;
				m_positionselect.y += 300.f;

				for (int i = 0; i < button; i++) {
					SpriteRender* sp = NewGO<SpriteRender>(16, "menuselectsieat");
					sp->Init(L"Assets/sprite/menuselectsieat.dds", 350, 120, true);
					m_positionselect.y -= 200.f;
					sp->SetPosition(m_positionselect);
					m_buttons.push_back(sp);
					m_fonts.push_back(NewGO<FontRender>(17));
					m_fonts[i]->SetTextType(CFont::en_Japanese);
				}
				//auto bacon = m_nodebuttons[0]->GetPos();
				CVector2 m_fontpos = CVector2::Zero();
				m_fontpos.x += m_positionselect.x -= 100;
				m_fontpos.y += m_positionselect.y += 220;
				m_fonts[0]->Init(L"セレクトメニューへ戻る", { m_fontpos }, 0.0, CVector4::Red, 1.0, { 0.0,0.0 });
				m_fontpos.y += m_positionselect.y -= 620;
				m_fonts[1]->Init(L"戻る", { m_fontpos }, 0.0, CVector4::Red, 1.0, { 0.0,0.0 });
				menu = true;
			}
		}
	}

}

void AIEditNodeMenu::Update()
{
	CVector3 cursorpos = m_gamecursor->GetCursor();

	m_spriterender2->SetCollisionTarget(cursorpos);

	Menuwin();

	if (menu == true) {

		m_spriteRender->SetCollisionTarget(cursorpos);

		if (Mouse::isTrigger(enLeftClick)) {	//左クリック
	
			if (m_spriteRender->isCollidingTarget()){
				BackMenu();
				m_aieditnodeprocess->AISave();
			}
		}
	}	
}
