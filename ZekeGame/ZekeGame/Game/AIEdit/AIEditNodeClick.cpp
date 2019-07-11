#include "stdafx.h"
#include "AIEditNodeClick.h"
#include "AIEditNode.h"
#include "AIEditLine.h"
#include "../GameCursor.h"
#include "AIEditNodeTarget.h"
//camera
#include "../../GameCamera.h"
#include "AIEditNodeProcess.h"
#include "AIEditNodeSelectButtons.h"

AIEditNodeClick::~AIEditNodeClick()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_button);
	DeleteGO(m_font);
}


bool AIEditNodeClick::Start()
{
	m_gamecursor = FindGO<GameCursor>("cursor");
	m_aieditnodeprocess = FindGO<AIEditNodeProcess>("process");

	m_spriteRender = NewGO<SpriteRender>(0, "mass");
	m_spriteRender->Init(L"Assets/sprite/click.dds", 250, 80,true); //last
	m_position.y += 2.f;                                            //謎の微調整。
	m_spriteRender->SetPosition(m_position);

	m_button = NewGO<SpriteRender>(0, "sp");
	m_button->Init(L"Assets/sprite/clickButton.dds", 57, 57);
	CVector3 v = m_position;
	v.x -= 80.f;
	m_button->SetPosition(v);

	m_font = NewGO<FontRender>(0, "font");
	m_font->SetTextType(CFont::en_Japanese);
	CVector2 v2 = v.ToTwo();
	v2.x += 40;
	v2.y += 17;
	m_font->Init(L"クリック", v2, 0, { 1.0f,0.7f,0.3f,1 }, 0.7f);
	m_font->DrawShadow();

	 m_aieditnodeselectbuttons = FindGO<AIEditNodeSelectButtons>("selectbuttons");
	return true;

}

void AIEditNodeClick::SetPosition(CVector3 m_pos)
{
	m_position = m_pos;

}

void AIEditNodeClick::Update()
{
	CVector3 cursorpos = m_gamecursor->GetCursor();
	
	if (m_aieditnodeselectbuttons->GetMenuSelect()) return;

	m_spriteRender->SetCollisionTarget(cursorpos);

	if (Choice0 == false) {
		if (m_spriteRender->isCollidingTarget()) {

			if (Mouse::isTrigger(enLeftClick)) {
				m_aieditnodetarget = NewGO<AIEditNodeTarget>(0, "target");

				Choice0 = true;
				PlayButtonSE();

				m_aieditnodeprocess->SetTechniqueGenerate(false);
				m_aieditnodeprocess->ClickClicking();
			}
			if (!m_isOver)
			{
				m_button->SetMulCol({ 0.6f,0.6f,0.6f,1 });
				m_button->SetScale({ 0.95f,0.95f, 0.95f });
				m_isOver = true;
				CVector4 c = CVector4{ 1.0f,0.7f,0.3f,1 };
				m_font->SetColor(c);
			}
		}
		else if(m_isOver)
		{
			m_button->SetMulCol(CVector4::White);
			m_button->SetScale(CVector3::One());
			m_isOver = false;
			m_fontS = 1;
		}
		else
		{
			if (m_fontS > 1.3)
			{
				
				m_isFsc = true;

			}
			else if (m_fontS < 1.0f)
			{
				
				m_isFsc = false;

			}

			if (!m_isFsc)
			{
				m_fontS += 0.005f;
			}
			else
			{
				m_fontS -= 0.005f;
			}

			CVector4 c = CVector4{ 1.0f,0.7f,0.3f,1 }*m_fontS;
			c.w = 1;
			m_font->SetColor(c);
		}
	}
}


