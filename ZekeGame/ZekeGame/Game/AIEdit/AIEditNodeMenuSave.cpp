#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditNodeMenuSave.h"
#include "AIEditNodeMenu.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeSelectButtons.h"

#include "VisualAIOpen.h"

AIEditNodeMenuSave::~AIEditNodeMenuSave()
{
	

}

void AIEditNodeMenuSave::OnDestroy()
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

	for (auto sp : m_buttonsF)
		DeleteGO(sp);
	for (auto fr : m_fontsF)
		DeleteGO(fr);
	DeleteGO(m_close);
	DeleteGO(m_cfont);
	DeleteGO(m_head);
	DeleteGO(m_back);

	for (auto sp : m_palette)
		DeleteGO(sp);
	DeleteGO(m_backC);
	DeleteGO(m_headC);
}


void AIEditNodeMenuSave::Awake()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodemenu = FindGO<AIEditNodeMenu>("menu");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_aieditselectbuttons = FindGO<AIEditNodeSelectButtons>("selectbuttons");

	/*m_spriteRender = NewGO<SpriteRender>(17, "menuconf");
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
	m_fonts[1]->Init(L"いいえ", { m_fontpos }, 0.0, CVector4::White, 1.0, { 0.0,0.0 });*/

	std::vector<VisualAIState> vass = VisualAIOpen::openVAs();
	

	//ファイルの選択GUI
	m_back = NewGO<SpriteRender>(10, "sp");
	m_back->Init(L"Assets/sprite/fade_black.dds", 740, 700);

	CVector3 pos = { -357.5f,175.f,0 };
	int len = vass.size();
	int vasc = 999;
	if(vass.size()!=0)
		vasc = vass[0].num;
	for (int i = 0; i < 12; i++)
	{
		if (i == 4)
			pos = { -357.5f,-5.f,0 };
		else if (i == 8)
			pos = { -357.5f,-185.f,0 };

		SpriteRender* sp = NewGO<SpriteRender>(11, "sp");
		FontRender* fr = NewGO<FontRender>(11, "fr");
		if (vasc != 999 and i == vass[vasc].num)
		{
			sp->Init(L"Assets/sprite/fade_black.dds", 175, 175, true);
			sp->SetMulCol(vass[vasc].col);
			sp->SetPivot({ 0.f,0.5f });
			sp->SetPosition(pos);

			wchar_t tx[3] = {'\0'};
			swprintf_s(tx, L"%d", vass[vasc].num);
			fr->Init(tx, (pos + CVector3(0, 87.5f, 0)).ToTwo(), 0, { 1,1,1,1 },0.8f);
			fr->SetTextType(CFont::en_JapaneseBIG);
			fr->DrawShadow();
			m_fontsF.push_back(fr);
			if(vasc+1 < len)
				vasc++;
		}
		else
		{
			sp->Init(L"Assets/sprite/fade_black.dds", 175, 175, true);
			sp->SetMulCol({ 0.6f,0.6f ,0.6f ,1 });
			sp->SetPivot({ 0.f,0.5f });
			sp->SetPosition(pos);

			fr->Init(L"なし", (pos + CVector3(0, 43.75f, 0)).ToTwo(), 0, { 0.8f,0.8f,0.8f,1 },0.4f);
			fr->SetTextType(CFont::en_JapaneseBIG);
			fr->DrawShadow();
			m_fontsF.push_back(fr);
		}
		pos.x += 180;

		m_buttonsF.push_back(sp);
	}

	m_head = NewGO<FontRender>(11, "fr");
	m_head->SetTextType(CFont::en_JapaneseBIG);
	m_head->Init(L"保存する場所を選択してください", { -340,330.5f }, 0, { 1,1,1,1 }, 0.27f, { 0.5f,1.f });
	m_head->DrawShadow();

	m_close = NewGO<SpriteRender>(11, "sr");
	m_close->Init(L"Assets/sprite/fade_black.dds", 160, 64, true);
	m_close->SetPosition({ 357.5f ,-345,0 });
	m_close->SetPivot({ 1,0 });
	m_close->SetMulCol({ 0.5,0.5,0.5,1 });

	m_cfont = NewGO<FontRender>(12, "fr");
	m_cfont->Init(L"とじる", { 210.0f ,-290 }, 0, { 1,1,1,1 }, 1);
	m_cfont->SetTextType(CFont::en_Japanese);
	m_cfont->DrawShadow();
}

bool AIEditNodeMenuSave::Start()
{
	
	
	return true;
}

void AIEditNodeMenuSave::Confirmation()
{

	m_spriteRender2 = NewGO<SpriteRender>(22, "sp");
	m_spriteRender2->Init(L"Assets/sprite/menu.dds", 260, 160, true);
	m_spriteRender2->SetPosition(m_Confirmationposition);

	m_spriteRender3 = NewGO<SpriteRender>(22, "sp");
	m_spriteRender3->Init(L"Assets/sprite/menuselectsieat.dds", 160, 80, true);
	m_Confirmationposition.y -= 25.f;
	m_spriteRender3->SetPosition(m_Confirmationposition);

	

	m_fonts4 = NewGO<FontRender>(23);
	m_fonts4->SetTextType(CFont::en_Japanese);
	m_fonts3 = NewGO<FontRender>(23);
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

void AIEditNodeMenuSave::AISelected()
{
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
}

void AIEditNodeMenuSave::confProc()
{
	if (!clickyes)
	{
		for (int i = 0; i < button; i++) {

			sp[i]->SetCollisionTarget(cursorpos);
		}

		if (click == false) {
			if (Mouse::isTrigger(enLeftClick)) {
				if (sp[button - 2]->isCollidingTarget()) {		//　はい　を選択した場合。

					//m_aieditnodeprocess->AISave();

					PaletteInit();


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
		PaletteProc();
		/*if (stop == false) {
			Confirmation();
			stop = true;
		}
		m_spriteRender3->SetCollisionTarget(cursorpos);

		if (m_spriteRender3->isCollidingTarget()) {
			if (Mouse::isTrigger(enLeftClick)) {
				m_aieditselectbuttons->Setmenuselect(false);
				DeleteGO(this);
			}
		}*/
	}
}

void AIEditNodeMenuSave::PaletteInit()
{
	CVector3 posp = { 160,-30,0 };
	m_backC = NewGO<SpriteRender>(20, "sp");
	m_backC->Init(L"Assets/sprite/fade_black.dds", 740, 250);
	m_backC->SetPosition(posp);

	CVector3 pos = { -357.5f,-30.f,0 };
	pos += posp;
	for (int i = 0; i < 4; i++)
	{
		SpriteRender* sp = NewGO<SpriteRender>(21, "sp");
		sp->Init(L"Assets/sprite/fade_black.dds", 175, 175, true);
		sp->SetPivot({ 0,0.5f });
		sp->SetPosition(pos);
		
		CVector4 col = CVector4::Black;
		switch (i)
		{
		case 0:
			col = VisualAIOpen::Red();
			break;
		case 1:
			col = VisualAIOpen::Blu();
			break;
		case 2:
			col = VisualAIOpen::Yel();
			break;
		case 3:
			col = VisualAIOpen::Whi();
			break;
		}
		sp->SetMulCol(col);

		pos.x += 180;

		m_palette.push_back(sp);
	}

	m_headC = NewGO<FontRender>(21, "fr");
	m_headC->SetTextType(CFont::en_Japanese);
	pos = { -200,120,0 };
	pos += posp;
	m_headC->Init(L"色を選択してください", { pos.x,pos.y }, 0, CVector4::White, 1);
	m_headC->DrawShadow();

}

void AIEditNodeMenuSave::PaletteProc()
{
	if (!m_isColSel)
	{
		for (auto sp : m_palette)
		{
			sp->SetCollisionTarget(cursorpos);
		}
		if (Mouse::isTrigger(enLeftClick))
		{
			for (int i = 0; i < 4; i++)
			{
				if (m_palette[i]->isCollidingTarget())
				{
					m_selCol = i;
					Confirmation();
					m_isColSel = true;
				}
			}
		}
	}
	else
	{
		m_spriteRender3->SetCollisionTarget(cursorpos);

		if (m_spriteRender3->isCollidingTarget()) {
			if (Mouse::isTrigger(enLeftClick)) {
				m_aieditselectbuttons->Setmenuselect(false);
				DeleteGO(this);
			}
		}
	}
}

void AIEditNodeMenuSave::Update()
{
	cursorpos = m_gamecursor->GetCursor();
	if (!m_isSelected)
	{
		for (auto sp : m_buttonsF)
		{
			sp->SetCollisionTarget(cursorpos);
		}
		m_close->SetCollisionTarget(cursorpos);

		if (Mouse::isTrigger(enLeftClick))
		{
			for (int i = 0; i < 12; i++)
			{
				if (m_buttonsF[i]->isCollidingTarget())
				{
					m_SelectBlock = i;
					AISelected();
					m_isSelected = true;
				}
			}

			if (m_close->isCollidingTarget())
			{
				m_aieditselectbuttons->Setmenuselect(false);
				DeleteGO(this);
			}
		}
	}
	else
		confProc();
}