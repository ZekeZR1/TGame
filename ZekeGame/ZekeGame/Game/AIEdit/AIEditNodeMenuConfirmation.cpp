#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeMenuConfirmation.h"
#include "AIEditNodeMenu.h"


AIEditNodeMenuConfirmation::~AIEditNodeMenuConfirmation()
{
	DeleteGO(m_spriteRender);
	for (auto button : m_buttons)
		DeleteGO(button);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	DeleteGO(m_fonts2);
}


bool AIEditNodeMenuConfirmation::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodemenu = FindGO<AIEditNodeMenu>("menu");

	m_spriteRender = NewGO<SpriteRender>(17, "menuconf");
	m_spriteRender->Init(L"Assets/sprite/menu.dds", 520, 200, true);
	m_spriteRender->SetPosition(confpos);
	m_positionselect = confpos;
	m_positionselect.x -= 375;
	m_positionselect.y -= 35;

	for (int i = 0; i < button; i++) {

		sp.push_back(NewGO<SpriteRender>(18, "menuselectsieat"));
		sp[i]->Init(L"Assets/sprite/menuselectsieat.dds", 240, 120, true);
		m_positionselect.x += 250.f;
		sp[i]->SetPosition(m_positionselect);
		m_buttons.push_back(sp[i]);

		m_fonts.push_back(NewGO<FontRender>(19));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
		
	}
	m_fonts2 = NewGO<FontRender>(19);
	m_fonts2->SetTextType(CFont::en_Japanese);

	m_fontpos.x += m_positionselect.x;
	m_fontpos.y += m_positionselect.y;
	m_fontpos2.x += m_positionselect.x;
	m_fontpos2.y += m_positionselect.y;

	m_fontpos2.x -= 370;
	m_fontpos2.y += 120;
	m_fonts2->Init(L"警告：変更内容が破棄されます", { m_fontpos2 }, 0.0, CVector4::Red, 0.8, { 0.0,0.0 });

	m_fontpos.x -= 300.f;
	m_fonts[0]->Init(L"はい", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x += 225;
	m_fonts[1]->Init(L"いいえ", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });

	return true;

}


void AIEditNodeMenuConfirmation::Update()
{
	CVector3 cursorpos = m_gamecursor->GetCursor();

	for (int i = 0; i < button; i++) {

		sp[i]->SetCollisionTarget(cursorpos);
	}

	if (Mouse::isTrigger(enLeftClick)) {
		if (sp[button - 2]->isCollidingTarget()) {//　はい　を選択した場合。
			m_aieditnodemenu->BackMenu();
		}

		if (sp[button - 1]->isCollidingTarget()) {//　いいえ　を選択した場合。
			m_aieditnodemenu->SetMenuconf(false);
			DeleteGO(this);
		}

	}
}