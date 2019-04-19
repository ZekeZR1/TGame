#include "stdafx.h"
#include "AIEditNodeMenuOpen.h"

#include "AIEditNodeSelectButtons.h"
#include "../GameCursor.h"

#include "VisualAIOpen.h"

void AIEditNodeMenuOpen::OnDestroy()
{
	DeleteGO(m_back);
	for (auto sp : m_buttons)
		DeleteGO(sp);
	for (auto fr : m_fonts)
		DeleteGO(fr);
	DeleteGO(m_head);
	DeleteGO(m_close);
	DeleteGO(m_cfont);
}

void AIEditNodeMenuOpen::Awake()
{
	std::vector<VisualAIState> vass = VisualAIOpen::openVAs();

	m_back = NewGO<SpriteRender>(10, "sp");
	m_back->Init(L"Assets/sprite/fade_black.dds", 740, 700);

	CVector3 pos = { -357.5f,175.f,0 };
	int len = vass.size();
	int vasc = 999;
	if (vass.size() != 0)
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

			wchar_t tx[3] = { '\0' };
			swprintf_s(tx, L"%d", vass[vasc].num);
			fr->Init(tx, (pos + CVector3(0, 87.5f, 0)).ToTwo(), 0, { 1,1,1,1 }, 0.8f);
			fr->SetTextType(CFont::en_JapaneseBIG);
			fr->DrawShadow();
			m_fonts.push_back(fr);
			if (vasc + 1 < len)
				vasc++;
		}
		else
		{
			sp->Init(L"Assets/sprite/fade_black.dds", 175, 175);
			sp->SetMulCol({ 0.6f,0.6f ,0.6f ,1 });
			sp->SetPivot({ 0.f,0.5f });
			sp->SetPosition(pos);

			fr->Init(L"‚È‚µ", (pos + CVector3(0, 43.75f, 0)).ToTwo(), 0, { 0.8f,0.8f,0.8f,1 }, 0.4f);
			fr->SetTextType(CFont::en_JapaneseBIG);
			fr->DrawShadow();
			m_fonts.push_back(fr);
		}
		pos.x += 180;

		m_buttons.push_back(sp);
	}

	m_head = NewGO<FontRender>(11, "fr");
	m_head->SetTextType(CFont::en_JapaneseBIG);
	m_head->Init(L"ŠJ‚­AI‚ð‘I‘ð‚µ‚Ä‚­‚¾‚³‚¢", { -320,330.5f }, 0, { 1,1,1,1 }, 0.3f, { 0.5f,1.f });
	m_head->DrawShadow();

	m_close = NewGO<SpriteRender>(11, "sr");
	m_close->Init(L"Assets/sprite/fade_black.dds", 160, 64, true);
	m_close->SetPosition({ 357.5f ,-345,0 });
	m_close->SetPivot({ 1,0 });
	m_close->SetMulCol({ 0.5,0.5,0.5,1 });

	m_cfont = NewGO<FontRender>(12, "fr");
	m_cfont->Init(L"‚Æ‚¶‚é", { 210.0f ,-290 }, 0, {1,1,1,1},1);
	m_cfont->SetTextType(CFont::en_Japanese);
	m_cfont->DrawShadow();
}

bool AIEditNodeMenuOpen::Start()
{
	return true;
}

void AIEditNodeMenuOpen::Update()
{
	CVector3 cpos = m_cursor->GetCursor();
	m_close->SetCollisionTarget(cpos);
	if (Mouse::isTrigger(enLeftClick))
	{
		if (m_close->isCollidingTarget())
		{
			m_nsb->Setmenuselect(false);
			DeleteGO(this);
		}
	}
}
