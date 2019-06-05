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
#include "AIEditNodeSelectButtons.h"
#include "AIEditNodeBackGround.h"
#include "AIEditNodeDeleteKey.h"

AIEditNodeMenu::~AIEditNodeMenu()
{
	DeleteGO(m_spriteRender);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	for (auto button : m_buttons)
		DeleteGO(button);
}


bool AIEditNodeMenu::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_aieditnodeselectbuttons = FindGO<AIEditNodeSelectButtons>("selectbuttons");

	Menuwin();

	return true;
}

void AIEditNodeMenu::BackMenu()
{

	/*QueryGOs<AIEditLine>("Line", [&](AIEditLine* go)->bool
	{
		DeleteGO(go);
		return true;
	});*/

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

	QueryGOs<AIEditNodeOrder>("order", [&](AIEditNodeOrder* go)->bool
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

	QueryGOs<AIEditNodeBackGround>("background", [&](AIEditNodeBackGround*go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeSelectButtons>("selectbuttons", [&](AIEditNodeSelectButtons*go)->bool
	{
		DeleteGO(go);
		return true;
	});

	QueryGOs<AIEditNodeDeleteKey>("deletekey", [&](AIEditNodeDeleteKey*go)->bool
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
			CVector2 fp = m_fontpos;
			fp.y -= 20;
			fp.x -= 15;
			m_fonts[0]->Init(L"タイトルへ", { fp }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
			m_fontpos.y += m_positionselect.y -= 320;
			m_fonts[1]->Init(L"特殊技一覧", { m_fontpos.x-15,m_fontpos.y }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
			m_fontpos.y += m_positionselect.y += 20;
			m_fonts[2]->Init(L"戻る", { m_fontpos.x+50,m_fontpos.y }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
			menu = true;

		}

}


void AIEditNodeMenu::Update()
{
	bool isLeftClick = Mouse::isTrigger(enLeftClick);
	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {

		sp[i]->SetCollisionTarget(cursorpos);
	}

	if (menu == true) {
		m_spriteRender->SetCollisionTarget(cursorpos);
		//メニューセレクトへ戻るを選択した場合。
		if (sp[button - 3]->isCollidingTarget()) {
			sp[button - 3]->SetMulCol({ 1.3f,1.3f, 1.3f, 1 });
			if (Mouse::isTrigger(enLeftClick)) {	//左クリック
				if (menuconf == false) {
					m_aieditnodemenuconfirmation = NewGO<AIEditNodeMenuConfirmation>(0, "menuconf");
					menuconf = true;
					PlayButtonSE();

				}
			}
		}
		else
		{
			sp[button - 3]->SetMulCol(CVector4::White);
		}

		//特殊技一覧を選択した場合。
		if (sp[button - 2]->isCollidingTarget()) {
			sp[button - 2]->SetMulCol({ 1.3f,1.3f, 1.3f, 1 });
			if (Mouse::isTrigger(enLeftClick)) {	//左クリック
				PlayButtonSE();
			}
		}
		else
		{
			sp[button - 2]->SetMulCol(CVector4::White);
		}

		//戻るを選択した場合。
		if (sp[button - 1]->isCollidingTarget()) {
			sp[button - 1]->SetMulCol({ 1.3f,1.3f, 1.3f, 1 });
			if (Mouse::isTrigger(enLeftClick)) {	//左クリック
				m_aieditnodeselectbuttons->Setmenuselect(false);
				PlayButtonSE();
				DeleteGO(this);
			}
		}
		else
		{
			sp[button - 1]->SetMulCol(CVector4::White);
		}
	}	
}
