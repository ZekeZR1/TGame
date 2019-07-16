#include "stdafx.h"
#include "AIEditLine.h"
#include "AIEditNodeOrder.h"
#include "AIEditNode.h"
#include "../GameCursor.h"
#include "AIEditNodeTarget.h"
#include "AIEditNodeProcess.h"
#include"AIEditNodeSelectFonts.h"

//camera
#include "../../GameCamera.h"
AIEditLine::~AIEditLine()
{
	
}

void AIEditLine::OnDestroy()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_font);
}

bool AIEditLine::Start()
{
	if (m_ismakeLine)
		return true;

	m_aieditnode = FindGO<AIEditNode>("window");
	m_aieditnodeorder = FindGO<AIEditNodeOrder>("Order");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");
	m_spriteRender = NewGO<SpriteRender>(1, "line");
	m_spriteRender->Init(L"Assets/sprite/arrow.dds", 1, 40);  //last
	m_pos.x += 120;
	m_spriteRender->SetPosition(m_pos);
	m_spriteRender->SetPivot({ 0.0f, 0.5f });

	return true;
}

void AIEditLine::Update()
{
	if (m_ismakeLine)
		return;
	//矢印を拡大していくよ。
	if (x <= Expansion) {

		x += ExpansionRate;

		m_spriteRender->SetScale({x,1,1});

	}
	
	if (x >= Expansion) {
	
		if (Choice1 == false) {
			
			//「のとき」を矢印上に表示。
			m_font = NewGO<FontRender>(1, "fr");
			m_font->SetTextType(CFont::en_Japanese);
			CVector2 v = m_pos.ToTwo();
			v.x += 30;
			v.y += 8;
			m_font->Init(L"の と き", v, 0, { 0.f,0.f,0.f,1 }, 0.3f);

			m_aieditnodeprocess->Target();
			Choice1 = true;
		}
	}
}

void AIEditLine::makeLine()
{
	m_spriteRender = NewGO<SpriteRender>(1, "line");
	m_spriteRender->Init(L"Assets/sprite/arrow.dds", 1, 40);  //last
	
	m_pos.x += 120;
	m_spriteRender->SetPosition(m_pos);
	m_spriteRender->SetPivot({ 0.0f, 0.5f });
	m_ismakeLine = true;
	m_spriteRender->SetScale({ 182,1,1 });

	m_font = NewGO<FontRender>(1, "fr");
	m_font->SetTextType(CFont::en_Japanese);
	CVector2 v = m_pos.ToTwo();
	v.x += 30;
	v.y += 8;
	m_font->Init(L"の と き", v, 0, { 0.f,0.f,0.f,1 }, 0.3f);
}
