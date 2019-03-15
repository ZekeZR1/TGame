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
#include "AIEditNodeMenuConfirmation.h"
#include "AIEditNodeMenuWindow.h"
#include "AIEditNodeSelectFonts.h"

AIEditNodeMenu::~AIEditNodeMenu()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_spriterender2);
	DeleteGO(m_spriterender3);
	DeleteGO(m_spriterender4);
	DeleteGO(m_spriterender5);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	for (auto button : m_buttons)
		DeleteGO(button);
}


bool AIEditNodeMenu::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	m_spriterender2 = NewGO<SpriteRender>(2,"menu");
	m_spriterender2->Init(L"Assets/sprite/menuselect.dds", 80, 40, true);
	m_position2.x += 585;
	//m_position2.y += 338;
	m_position2.y += 300;    //仮
	m_spriterender2->SetPosition(m_position2);

	m_spriterender3 = NewGO<SpriteRender>(2, "menu");
	m_spriterender3->Init(L"Assets/sprite/help.dds", 40, 40, true);
	m_position3.x += 330;
	m_position3.y += 340;
	m_spriterender3->SetPosition(m_position3);

	m_spriterender4 = NewGO<SpriteRender>(2, "menu");
	m_spriterender4->Init(L"Assets/sprite/hozon.dds", 80, 40, true);
	m_position4.x += 500;
	//m_position4.y += 340;
	m_position4.y += 300;  // 仮。
	m_spriterender4->SetPosition(m_position4);

	m_spriterender5 = NewGO<SpriteRender>(2, "menu");
	m_spriterender5->Init(L"Assets/sprite/open.dds", 80, 40, true);
	m_position5.x += 415;
	//m_position4.y += 340;
	m_position5.y += 300;  // 仮。
	m_spriterender5->SetPosition(m_position5);

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

	QueryGOs<AIEditNodeMenuConfirmation>("menuconf", [&](AIEditNodeMenuConfirmation*go)->bool 
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeSelectFonts>("fonts", [&](AIEditNodeSelectFonts*go)->bool 
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

	//m_aieditnodemenuwindow = NewGO<AIEditNodeMenuWindow>(0, "menuwin");

	if (Mouse::isTrigger(enLeftClick)) {	//左クリック

		if (m_spriterender2->isCollidingTarget()) {

			if (menu == false) {
				m_spriteRender = NewGO<SpriteRender>(15, "menu");
				m_spriteRender->Init(L"Assets/sprite/menu.dds", 400, 400, true);
				m_spriteRender->SetPosition(m_position);
				m_positionselect = m_position;
				m_positionselect.y += 260.f;

				for (int i = 0; i < button; i++) {
				    sp.push_back(NewGO<SpriteRender>(16, "menuselectsieat"));
					sp[i]->Init(L"Assets/sprite/menuselectsieat.dds", 350, 120, true);
					m_positionselect.y -= 130.f;
					sp[i]->SetPosition(m_positionselect);
					m_buttons.push_back(sp[i]);
					m_fonts.push_back(NewGO<FontRender>(17));
					m_fonts[i]->SetTextType(CFont::en_Japanese);
				}

				CVector2 m_fontpos = CVector2::Zero();
				m_fontpos.x += m_positionselect.x -= 100;
				m_fontpos.y += m_positionselect.y += 300;
				m_fonts[0]->Init(L"セレクトメニューへ戻る", { m_fontpos }, 0.0, CVector4::Red, 1.0, { 0.0,0.0 });
				m_fontpos.y += m_positionselect.y -= 320;
				m_fonts[1]->Init(L"特殊技一覧", { m_fontpos }, 0.0, CVector4::Red, 1.0, { 0.0,0.0 });
				m_fontpos.y += m_positionselect.y += 20;
				m_fonts[2]->Init(L"戻る", { m_fontpos }, 0.0, CVector4::Red, 1.0, { 0.0,0.0 });
				menu = true;

			}
		}
	}
}


void AIEditNodeMenu::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();
	if (menuselect == false) {
		m_spriterender2->SetCollisionTarget(cursorpos);
		if (Mouse::isTrigger(enLeftClick)) {
			if (m_spriterender2->isCollidingTarget()) {
				Menuwin();
				menuselect = true;
			}
		}
	}

	if(menuselect == true){
		for (int i = 0; i < button; i++) {
			//SpriteRender* sp2 = sp[i];
			sp[i]->SetCollisionTarget(cursorpos);
		}
	}

	if (menu == true) {
		m_spriteRender->SetCollisionTarget(cursorpos);
		if (Mouse::isTrigger(enLeftClick)) {	//左クリック
			
			//メニューセレクトへ戻るを選択した場合。
			if (sp[button - 3]->isCollidingTarget()) {
				if (menuconf == false) {
					m_aieditnodemenuconfirmation = NewGO<AIEditNodeMenuConfirmation>(0, "menuconf");
					//m_aieditnodeprocess->AISave();
					menuconf = true;
				}
			}

			//特殊技一覧を選択した場合。
			if (sp[button - 2]->isCollidingTarget()) {

			}

			//戻るを選択した場合。
			if (sp[button - 1]->isCollidingTarget()) {
				//DeleteGO(Menuwin);
			}
		}
	}	
}
