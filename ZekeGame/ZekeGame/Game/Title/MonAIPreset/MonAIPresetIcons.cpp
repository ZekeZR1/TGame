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

void MonAIPresetIcons::init(Preset* preset, CVector3 pos,GameCursor* cur)
{
	m_cursor = cur;
	m_pos = pos;
	CVector3 ipos = pos;
	int cnt = 0;

	if (preset->person[0]->monID == 255)
	{
		CVector3 iipos = pos;
		iipos.x -= 80;
		iipos.y += 10;
		m_Nonefont = NewGO<FontRender>(6, "fr");
		m_Nonefont->SetTextType(CFont::en_JapaneseBIG);
		m_Nonefont->Init(L"な\n\nし", iipos.ToTwo(), 0, { 0.6f,0.6f,0.6f,1.0f }, 0.7f, { 1,0 });
		m_fontpos = iipos;
		m_isNone = 1;
	}
	else for (auto p : preset->person)
	{
		MonAIPresetIcon* mapicon = NewGO<MonAIPresetIcon>(0, "icon");

		wchar_t ws[255];
		setlocale(LC_ALL, "japanese");
		size_t size = 0;
		mbstowcs_s(&size, ws, 20, p->str, _TRUNCATE);

		mapicon->init(p->monID, ws,ipos);
		ipos.y -= 180;

		m_mapi[cnt] = mapicon;
		cnt++;
	}

	ipos = pos;
	ipos.y -= 190;
	ipos.y += 20;
	//ipos.x += 2;

	m_back = NewGO<SpriteRender>(5, "sp");
	m_back->Init(L"Assets/sprite/preset_back.dds", 157, 567);
	if (preset->person[0]->monID == 255)
		m_back->SetMulCol({ 0.2f,0.2f,0.2f,1.0f });
	m_back->SetPosition(ipos);

	m_dummy = NewGO<SpriteRender>(0, "sp");
	m_dummy->Init(L"Assets/sprite/.dds", 157, 567,true);
	m_dummy->SetPosition(ipos);

	m_preset = preset;
}

void MonAIPresetIcons::UpdateIcon()
{
	if (m_isNone)
	{
		CVector3 ipos = m_pos;
		int cnt = 0;
		for (auto p : m_preset->person)
		{
			MonAIPresetIcon* mapicon = NewGO<MonAIPresetIcon>(0, "icon");

			wchar_t ws[255];
			setlocale(LC_ALL, "japanese");
			size_t size = 0;
			mbstowcs_s(&size, ws, 20, p->str, _TRUNCATE);

			mapicon->init(p->monID, ws, ipos);
			ipos.y -= 180;

			m_mapi[cnt] = mapicon;
			cnt++;
		}
		m_isNone = 0;

		DeleteGO(m_Nonefont);
		m_Nonefont = nullptr;
		m_back->SetMulCol({1,1,1.f,1.0f });
	}
	
	for (int i=0;i<3;i++)
	{
		wchar_t ws[255];
		setlocale(LC_ALL, "japanese");
		size_t size = 0;
		mbstowcs_s(&size, ws, 20, m_preset->person[i]->str, _TRUNCATE);
		m_mapi[i]->UpdateAIMON(m_preset->person[i]->monID, ws);
	}
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
			m_back->Init(L"Assets/sprite/preset_back_sel.dds", 157, 567);
			m_isSelect = true;
		}
	}
	else
	{
		if (m_isSelect)				//マウスオーバー解除のアクション
		{
			m_back->Init(L"Assets/sprite/preset_back.dds", 157, 567);
			m_isSelect = false;
		}
	}
}

void MonAIPresetIcons::Setpos(CVector3 pos)
{
	CVector3 ipos = pos;
	int cnt = 0;

	if (m_preset->person[0]->monID == 255)
	{
		CVector3 iipos = pos;
		iipos.x -= 80;
		iipos.y += 10;
		m_Nonefont->SetPosition(iipos.ToTwo());
	}
	else for (auto p : m_preset->person)
	{
		m_mapi[cnt]->Setpos(ipos);
		ipos.y -= 180;
		cnt++;
	}

	ipos = pos;
	ipos.y -= 190;
	ipos.y += 19;
	m_back->SetPosition(ipos);
	m_dummy->SetPosition(ipos);
}

void MonAIPresetIcons::Setrot(float rot)
{
	CQuaternion qrot;
	qrot.SetRotationDeg(CVector3::AxisZ(), rot);

	m_back->SetRotation(qrot);
	if (m_preset->person[0]->monID == 255)
	{
		m_Nonefont->SetRotation(CMath::DegToRad(rot * -1));
		//m_Nonefont->SetPosition((m_fontpos).ToTwo());
	}
	else
	{
		for (auto icon : m_mapi)
		{
			icon->Setrot(rot, m_back->GetPosition());
		}
	}
}
