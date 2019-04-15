#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeMenuSave.h"
#include "AIEditNodeMenu.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeSelectButtons.h"

AIEditNodeMenuSave::~AIEditNodeMenuSave()
{
	if (m_spriteRender != nullptr) {
		DeleteGO(m_spriteRender);
	}
	DeleteGO(m_spriteRender2);
	DeleteGO(m_spriteRender3);
	for (auto button : sp)
		DeleteGO(button);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);
	DeleteGO(m_fonts2);
	DeleteGO(m_fonts3);
	DeleteGO(m_fonts4);

}


bool AIEditNodeMenuSave::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodemenu = FindGO<AIEditNodeMenu>("menu");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_aieditselectbuttons = FindGO<AIEditNodeSelectButtons>("selectbuttons");

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
	m_fonts2->Init(L"保存しますか", { m_fontpos2 }, 0.0, CVector4::Red, 0.8, { 0.0,0.0 });

	m_fontpos.x -= 300.f;
	m_fonts[0]->Init(L"はい", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	m_fontpos.x += 225;
	m_fonts[1]->Init(L"いいえ", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });
	
	return true;

}

void AIEditNodeMenuSave::Confirmation()
{

	m_spriteRender2 = NewGO<SpriteRender>(20, "sp");
	m_spriteRender2->Init(L"Assets/sprite/menu.dds", 260, 160, true);
	m_spriteRender2->SetPosition(m_Confirmationposition);

	m_spriteRender3 = NewGO<SpriteRender>(20, "sp");
	m_spriteRender3->Init(L"Assets/sprite/menuselectsieat.dds", 160, 80, true);
	m_Confirmationposition.y -= 25.f;
	m_spriteRender3->SetPosition(m_Confirmationposition);

	

	m_fonts4 = NewGO<FontRender>(21);
	m_fonts4->SetTextType(CFont::en_Japanese);
	m_fonts3 = NewGO<FontRender>(21);
	m_fonts3->SetTextType(CFont::en_Japanese);

	m_fontpos2.x += m_positionselect2.x += 140.f;
	m_fontpos2.y += m_positionselect2.y -= 20.f;
	m_fontpos3.x += m_Confirmationposition.x -= 55.f;
	m_fontpos3.y += m_Confirmationposition.y += 10.f;

	m_fonts4->Init(L"保存しました", { m_fontpos2 }, 0.0, CVector4::Red, 0.8, { 0.0,0.0 });
	m_fonts3->Init(L"とじる", { m_fontpos3 }, 0.0, CVector4::White, 0.8, { 0.0,0.0 });

	//if (Mouse::isTrigger(enLeftClick)) {
	//	if (m_spriteRender3->isCollidingTarget())
	//	{
	//		DeleteGO(this);
	//	}
	//}

}

void AIEditNodeMenuSave::Update()
{

	cursorpos = m_gamecursor->GetCursor();
	if (!clickyes)
	{
		for (int i = 0; i < button; i++) {

			sp[i]->SetCollisionTarget(cursorpos);
		}

		if (click == false) {
			if (Mouse::isTrigger(enLeftClick)) {
				if (sp[button - 2]->isCollidingTarget()) {		//　はい　を選択した場合。

					m_aieditnodeprocess->AISave();
					

					DeleteGO(m_spriteRender);
					m_spriteRender = nullptr;
					DeleteGO(m_fonts2);
					m_fonts2 = nullptr;
					for (int i = 0; i < 2; i++) {
						DeleteGO(sp[i]);
						sp[i] = nullptr;
						DeleteGO(m_fonts[i]);
						m_fonts[i] = nullptr;
					}

					clickyes = true;

					//Confirmation();

					click = true;
				}

				else if (sp[button - 1]->isCollidingTarget()) {		//　いいえ　を選択した場合。
					m_aieditselectbuttons->Setmenuselect(false);
					DeleteGO(this);

					click = true;
				}

			}
		}
	}
	else 
	{
		if (stop == false) {
			Confirmation();
			stop = true;
		}
		m_spriteRender3->SetCollisionTarget(cursorpos);

		if (m_spriteRender3->isCollidingTarget()) {
			if (Mouse::isTrigger(enLeftClick)) {
				m_aieditselectbuttons->Setmenuselect(false);
				DeleteGO(this);
			}
		}
	}

}