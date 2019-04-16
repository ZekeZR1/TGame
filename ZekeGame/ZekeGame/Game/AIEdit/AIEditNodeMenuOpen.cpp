#include "stdafx.h"
#include "AIEditNodeMenuOpen.h"

void AIEditNodeMenuOpen::OnDestroy()
{
}

void AIEditNodeMenuOpen::Awake()
{
	m_back = NewGO<SpriteRender>(10, "sp");
	m_back->Init(L"sprit/fade/fade_black.dds", 720, 700);

	for (int i = 0; i < 8; i++)
	{
		SpriteRender* sp = NewGO<SpriteRender>(11, "sp");

		sp->Init(L"sprite/fade/fade_black.dds", 80, 680);
		//sp->
		

		m_buttons.push_back(sp);
	}
}

bool AIEditNodeMenuOpen::Start()
{
	return true;
}

void AIEditNodeMenuOpen::Update()
{
}
