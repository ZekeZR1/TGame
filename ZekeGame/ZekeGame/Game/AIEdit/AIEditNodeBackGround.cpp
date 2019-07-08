#include "stdafx.h"
#include "../GameCursor.h"
#include "AIEditMode.h"
#include "AIEditNodeBackGround.h"

AIEditNodeBackGround::~AIEditNodeBackGround()
{
	DeleteGO(m_spriteRender);
	for (auto fonts : m_fonts)
		DeleteGO(fonts);

}

bool AIEditNodeBackGround::Start()
{
	m_spriteRender = NewGO<SpriteRender>(0, "backgorund");
	m_spriteRender->Init(L"Assets/sprite/haik.dds", 1280, 720);
	m_spriteRender->SetPosition(m_position);

	for (int i = 0; i < num; i++) {
		m_fonts.push_back(NewGO<FontRender>(1));
		m_fonts[i]->SetTextType(CFont::en_Japanese);
	}

	CVector2 m_pos2 = CVector2::Zero();
	m_pos2.x -= 560.f;
	m_pos2.y += 360.f;

	m_fonts[0]->Init(L"ŠÈ’PAI§ìƒ‚[ƒh", { m_pos2 }, 0.0, CVector4::White, 0.78, { 0.0,0.0 });
	m_fonts[0]->DrawShadow({ 5,-5 });
	
	m_pos2.x -= 55.f;
	m_pos2.y -= 60.f;
	m_fonts[1]->Init(L"1", { m_pos2 }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fonts[1]->DrawShadow({ 5,-5 });

	m_pos2.y -= 85.f;
	m_fonts[2]->Init(L"2", { m_pos2 }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fonts[2]->DrawShadow({ 5,-5 });

	m_pos2.y -= 85.f;
	m_fonts[3]->Init(L"3", { m_pos2 }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fonts[3]->DrawShadow({ 5,-5 });

	m_pos2.y -= 85.f;
	m_fonts[4]->Init(L"4", { m_pos2 }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fonts[4]->DrawShadow({ 5,-5 });

	m_pos2.y -= 85.f;
	m_fonts[5]->Init(L"5", { m_pos2 }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fonts[5]->DrawShadow({ 5,-5 });

	m_pos2.y -= 85.f;
	m_fonts[6]->Init(L"6", { m_pos2 }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fonts[6]->DrawShadow({ 5,-5 });

	m_pos2.y -= 85.f;
	m_fonts[7]->Init(L"7", { m_pos2 }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fonts[7]->DrawShadow({ 5,-5 });

	m_pos2.y -= 85.f;
	m_fonts[8]->Init(L"8", { m_pos2 }, 0.0, CVector4::White, 0.9, { 0.0,0.0 });
	m_fonts[8]->DrawShadow({ 5,-5 });

	return true;
}

void AIEditNodeBackGround::Update()
{

}