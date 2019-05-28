#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeMenu.h"
#include "AIEditNodeSelectButtons.h"
#include "AIEditNodeMenuSave.h"
#include "AIEditNodeMenuOpen.h"

#include "AIEditNodeProcess.h"

AIEditNodeSelectButtons::~AIEditNodeSelectButtons()
{

	DeleteGO(m_spriterender2);
	DeleteGO(m_spriterender3);
	DeleteGO(m_spriterender4);
	DeleteGO(m_spriterender5);

	DeleteGO(m_fmenu);
	DeleteGO(m_fopen);
	DeleteGO(m_fsave);

}


bool AIEditNodeSelectButtons::Start()
{
	m_proc = FindGO<AIEditNodeProcess>("process");
	m_gamecursor = FindGO<GameCursor>("cursor");
	CVector2 v;

	CVector2 xy = { -27.f, 13.f };

	///menu no yatu
	m_spriterender2 = NewGO<SpriteRender>(2, "menu");
	//m_spriterender2->Init(L"Assets/sprite/menuselect.dds", 80, 40, true);
	m_spriterender2->Init(L"Assets/sprite/HOM.dds", 80, 40, true);
	m_position2.x += 585;
	m_position2.y += 340;
	m_spriterender2->SetPosition(m_position2);
	
	m_fmenu = NewGO<FontRender>(2, "fr");
	v = m_position2.ToTwo();
	v = v + xy;
	v.x -= 13;
	v.y -= 5;
	m_fmenu->SetTextType(CFont::en_Japanese);
	m_fmenu->Init(L"MENU", v, 0, { 1,1,1,1 }, 0.46f);
	m_fmenu->DrawShadow();


	///help
	/*m_spriterender3 = NewGO<SpriteRender>(2, "menu");
	m_spriterender3->Init(L"Assets/sprite/help.dds", 40, 40, true);
	m_position3.x += 330;
	m_position3.y += 340;
	m_spriterender3->SetPosition(m_position3);*/
	m_position3.x += 330;
	m_position3.y += 340;

	///hozon no yatu
	m_spriterender4 = NewGO<SpriteRender>(2, "menu");
	//m_spriterender4->Init(L"Assets/sprite/hozon.dds", 80, 40, true);
	m_spriterender4->Init(L"Assets/sprite/HOM.dds", 80, 40, true);
	m_position4.x += 500;
	m_position4.y += 340;
	m_spriterender4->SetPosition(m_position4);

	m_fsave = NewGO<FontRender>(2, "fr");
	v = m_position4.ToTwo();
	v = v + xy;
	m_fsave->SetTextType(CFont::en_Japanese);
	m_fsave->Init(L"保存", v, 0, { 1,1,1,1 }, 0.6f);
	m_fsave->DrawShadow();


	///open no yatu
	m_spriterender5 = NewGO<SpriteRender>(2, "menu");
	//m_spriterender5->Init(L"Assets/sprite/open.dds", 80, 40, true);
	m_spriterender5->Init(L"Assets/sprite/HOM.dds", 80, 40, true);
	m_position5.x += 415;
	m_position5.y += 340;
	m_spriterender5->SetPosition(m_position5);

	m_fopen = NewGO<FontRender>(2, "fr");
	v = m_position5.ToTwo();
	v = v + xy;
	m_fopen->SetTextType(CFont::en_Japanese);
	m_fopen->Init(L"開く", v, 0, { 1,1,1,1 }, 0.6f);
	m_fopen->DrawShadow();

	return true;
}


void AIEditNodeSelectButtons::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	if (menuselect == false) {
		bool isClick = Mouse::isTrigger(enLeftClick);

		//メニューを表示する。	
		m_spriterender2->SetCollisionTarget(cursorpos);
		if (m_spriterender2->isCollidingTarget()) {
			if (isClick) {
				m_aieditnodemenu = NewGO<AIEditNodeMenu>(0, "menu");
				menuselect = true;
			}
			if (!m_bmenu)
			{
				m_spriterender2->SetMulCol({ 1.4f,1.4f ,1.4f ,1 });
				m_bmenu = true;
			}
		}
		else if (m_bmenu)
		{
			m_spriterender2->SetMulCol({ 1.f,1.f ,1.f ,1 });
			m_bmenu = false;
		}

		//?をクリックしたときにhelpを表示する。
		//m_spriterender3->SetCollisionTarget(cursorpos);
		//if (m_spriterender3->isCollidingTarget()) {
		//	if (isClick) {
		//		//ここで何かをNew。
		//		menuselect = true;
		//	}
		//}

		if (m_proc->isClickClicked())
			return;

		//保存するためのwindowを表示する。
		m_spriterender4->SetCollisionTarget(cursorpos);
		if (m_spriterender4->isCollidingTarget()) {
			if (isClick) {
				m_aieditnodemenusave = NewGO<AIEditNodeMenuSave>(0, "menusave");
				menuselect = true;
			}
			if (!m_bsave)
			{
				m_spriterender4->SetMulCol({ 1.4f,1.4f ,1.4f ,1 });
				m_bsave = true;
			}
		}
		else if (m_bsave)
		{
			m_spriterender4->SetMulCol({ 1.f,1.f ,1.f ,1 });
			m_bsave = false;
		}

		//自分が保存していたものの一覧を表示する。
		m_spriterender5->SetCollisionTarget(cursorpos);
		if (m_spriterender5->isCollidingTarget()) {
			if (isClick) {
				//ここで何かをNew。
				m_aieditnodemenuopen = NewGO<AIEditNodeMenuOpen>(0, "menuopen");
				m_aieditnodemenuopen->init(this, m_gamecursor);
				menuselect = true;
			}
			if (!m_bopen)
			{
				m_spriterender5->SetMulCol({ 1.4f,1.4f ,1.4f ,1 });
				m_bopen = true;
			}
		}
		else if (m_bopen)
		{
			m_spriterender5->SetMulCol({ 1.f,1.f ,1.f ,1 });
			m_bopen = false;
		}

	}
}