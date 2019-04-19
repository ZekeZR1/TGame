#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeMenu.h"
#include "AIEditNodeSelectButtons.h"
#include "AIEditNodeMenuSave.h"
#include "AIEditNodeMenuOpen.h"


AIEditNodeSelectButtons::~AIEditNodeSelectButtons()
{

	DeleteGO(m_spriterender2);
	DeleteGO(m_spriterender3);
	DeleteGO(m_spriterender4);
	DeleteGO(m_spriterender5);

}


bool AIEditNodeSelectButtons::Start()
{

	m_gamecursor = FindGO<GameCursor>("cursor");

	m_spriterender2 = NewGO<SpriteRender>(2, "menu");
	m_spriterender2->Init(L"Assets/sprite/menuselect.dds", 80, 40, true);
	m_position2.x += 585;
	m_position2.y += 340;
	m_spriterender2->SetPosition(m_position2);

	m_spriterender3 = NewGO<SpriteRender>(2, "menu");
	m_spriterender3->Init(L"Assets/sprite/help.dds", 40, 40, true);
	m_position3.x += 330;
	m_position3.y += 340;
	m_spriterender3->SetPosition(m_position3);

	m_spriterender4 = NewGO<SpriteRender>(2, "menu");
	m_spriterender4->Init(L"Assets/sprite/hozon.dds", 80, 40, true);
	m_position4.x += 500;
	m_position4.y += 340;
	m_spriterender4->SetPosition(m_position4);

	m_spriterender5 = NewGO<SpriteRender>(2, "menu");
	m_spriterender5->Init(L"Assets/sprite/open.dds", 80, 40, true);
	m_position5.x += 415;
	m_position4.y += 340;
	m_spriterender5->SetPosition(m_position5);

	return true;
}


void AIEditNodeSelectButtons::Update()
{

	CVector3 cursorpos = m_gamecursor->GetCursor();

	if (menuselect == false) {

		//メニューを表示する。	
		m_spriterender2->SetCollisionTarget(cursorpos);
		if (m_spriterender2->isCollidingTarget()) {
			if (Mouse::isTrigger(enLeftClick)) {
				m_aieditnodemenu = NewGO<AIEditNodeMenu>(0, "menu");
				menuselect = true;
			}
		}

		//?をクリックしたときにhelpを表示する。
		m_spriterender3->SetCollisionTarget(cursorpos);
		if (m_spriterender3->isCollidingTarget()) {
			if (Mouse::isTrigger(enLeftClick)) {
				//ここで何かをNew。
				menuselect = true;
			}
		}

		//保存するためのwindowを表示する。
		m_spriterender4->SetCollisionTarget(cursorpos);
		if (m_spriterender4->isCollidingTarget()) {
			if (Mouse::isTrigger(enLeftClick)) {
				m_aieditnodemenusave = NewGO<AIEditNodeMenuSave>(0, "menusave");
				menuselect = true;
			}
		}

		//自分が保存していたものの一覧を表示する。
		m_spriterender5->SetCollisionTarget(cursorpos);
		if (m_spriterender5->isCollidingTarget()) {
			if (Mouse::isTrigger(enLeftClick)) {
				//ここで何かをNew。
				m_aieditnodemenuopen = NewGO<AIEditNodeMenuOpen>(0, "menuopen");
				m_aieditnodemenuopen->init(this, m_gamecursor);
				menuselect = true;
			}
		}

	}
}