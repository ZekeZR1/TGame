#include "stdafx.h"
#include "MonAIPresetIcons.h"

#include "MonAIPresetIcon.h"

#include "MonAIPresetOpenSuper.h"

#include "../../GameCursor.h"

void MonAIPresetIcons::OnDestroy()
{
	for (auto o : m_mapi)
	{
		DeleteGO(o);
	}
	DeleteGO(m_back);
	DeleteGO(m_dummy);
	if (m_Nonefont != nullptr)
		DeleteGO(m_Nonefont);
}

MonAIPresetIcons::~MonAIPresetIcons()
{

}

bool MonAIPresetIcons::Start()
{
	return true;
}

void MonAIPresetIcons::init(Preset preset, CVector3 pos,GameCursor* cur)
{
	m_cursor = cur;

	CVector3 ipos = pos;
	int cnt = 0;

	if (preset.person->monID == 0)
	{
		CVector3 iipos = pos;
		iipos.x -= 80;
		iipos.y += 10;
		m_Nonefont = NewGO<FontRender>(6, "fr");
		m_Nonefont->SetTextType(CFont::en_JapaneseBIG);
		m_Nonefont->Init(L"な\n\nし", iipos.ToTwo(), 0, { 0.6f,0.6f,0.6f,1.0f }, 0.7f, { 1,0 });
		
	}
	else for (auto p : preset.person)
	{
		MonAIPresetIcon* mapicon = NewGO<MonAIPresetIcon>(0, "icon");

		wchar_t ws[255];
		setlocale(LC_ALL, "japanese");
		size_t size = 0;
		mbstowcs_s(&size, ws, 20, p.str, _TRUNCATE);

		mapicon->init(p.monID, ws,ipos);
		ipos.y -= 180;

		m_mapi[cnt] = mapicon;
		cnt++;
	}

	ipos = pos;
	ipos.y -= 190;

	m_back = NewGO<SpriteRender>(5, "sp");
	m_back->Init(L"Assets/sprite/fade_black.dds", 150, 510);
	if (preset.person->monID == 0)
		m_back->SetMulCol({ 0.2f,0.2f,0.2f,1.0f });
	m_back->SetPosition(ipos);

	m_dummy = NewGO<SpriteRender>(0, "sp");
	m_dummy->Init(L"Assets/sprite/fade_black.dds", 150, 510,true);
	m_dummy->SetPosition(ipos);
}

void MonAIPresetIcons::Update()
{
	m_isClick = false;
	m_dummy->SetCollisionTarget(m_cursor->GetCursor());
	if (m_dummy->isCollidingTarget())
	{
		if (Mouse::isTrigger(enLeftClick))
		{
			m_isClick = true;
		}
		if (!m_isSelect)			//マウスオーバー時のアクション
		{
			m_isSelect = true;
		}
	}
	else
	{
		if (m_isSelect)				//マウスオーバー解除のアクション
		{
			m_isSelect = false;
		}
	}
}
