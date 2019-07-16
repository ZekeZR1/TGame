#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeMenuConfirmation.h"
#include "AIEditNodeMenu.h"
#include "AIEditNodeMenuWindow.h"

AIEditNodeMenuWindow::~AIEditNodeMenuWindow()
{
	DeleteGO(m_spriteRender);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	for (auto button : m_buttons)
		DeleteGO(button);

}

bool AIEditNodeMenuWindow::Start()
{
	m_aieditnodemenu = FindGO<AIEditNodeMenu>("menu");

	if (Mouse::isTrigger(enLeftClick)) {	//左クリック

		if (m_spriterender2->isCollidingTarget()) {

			if (m_aieditnodemenu->GetMenu() == false) {
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
				m_aieditnodemenu->SetMenu(true);

			}
		}
	}

	return true;
}

void AIEditNodeMenuWindow::Update()
{

}