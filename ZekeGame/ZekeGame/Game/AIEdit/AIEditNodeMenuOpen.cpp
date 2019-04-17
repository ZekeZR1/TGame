#include "stdafx.h"
#include "AIEditNodeMenuOpen.h"

void AIEditNodeMenuOpen::OnDestroy()
{
}

void AIEditNodeMenuOpen::Awake()
{
	m_back = NewGO<SpriteRender>(10, "sp");
	m_back->Init(L"Assets/sprite/fade_black.dds", 740, 700);

	CVector3 pos = { -357.5f,175.f,0 };
	for (int i = 0; i < 12; i++)
	{
		if (i == 4)
			pos = { -357.5f,-5.f,0 };
		else if(i == 8)
			pos = { -357.5f,-185.f,0 };
		SpriteRender* sp = NewGO<SpriteRender>(11, "sp");

		sp->Init(L"Assets/sprite/fade_black.dds", 175, 175);
		sp->SetMulCol({ 0.8,0.8,0.8,1 });
		sp->SetPivot({ 0.f,0.5f });
		sp->SetPosition(pos);
		pos.x += 180;

		m_buttons.push_back(sp);
	}

	m_head = NewGO<FontRender>(11, "fr");
	m_head->SetTextType(CFont::en_JapaneseBIG);
	m_head->Init(L"ŠJ‚­AI‚ð‘I‘ð‚µ‚Ä‚­‚¾‚³‚¢", { -320,330.5f }, 0, { 1,1,1,1 }, 0.3f, { 0.5f,1.f });
	m_head->DrawShadow();

	m_close = NewGO<SpriteRender>(11, "sr");
	m_close->Init(L"Assets/sprite/fade_black.dds", 160, 64, false);
	m_close->SetPosition({ 357.5f ,-345,0 });
	m_close->SetPivot({ 1,0 });
	m_close->SetMulCol({ 0.5,0.5,0.5,1 });
}

bool AIEditNodeMenuOpen::Start()
{
	return true;
}

void AIEditNodeMenuOpen::Update()
{
}
