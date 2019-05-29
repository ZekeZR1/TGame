#include "stdafx.h"
#include "MonAIPresetIcon.h"

#include "../../GameData.h"

void MonAIPresetIcon::OnDestroy()
{
	DeleteGO(m_Icon);
	DeleteGO(m_font);
}

MonAIPresetIcon::~MonAIPresetIcon()
{
	
}

bool MonAIPresetIcon::Start()
{
	return true;
}

void MonAIPresetIcon::init(int monID, const wchar_t* pypath,CVector3 pos)
{
	m_Icon = NewGO<SpriteRender>(20, "sp");
	m_Icon->Init(GameData::GetMonsterIconPath(monID), 150, 170);
	m_Icon->SetPosition(pos);

	m_pos = pos;

	pos.x -= 80;
	pos.y -= 30;

	std::wstring ws = pypath;
	int len = lstrlenW(pypath);
	if (len > 6)
	{
		ws[6] = L'\0';
		len = 6;
		pos.y -= 15;
	}
	float sc = len > 4 ? 4.f / float(len) : 1;

	m_font = NewGO<FontRender>(21, "fr");
	m_font->Init(ws.c_str(), pos.ToTwo(), 0, CVector4::White, sc, {0,0});
	m_font->DrawShadow();
}

void MonAIPresetIcon::Setpos(CVector3 pos)
{
	m_Icon->SetPosition(pos);
	m_pos = pos;

	pos.x -= 80;
	pos.y -= 30;

	int len = lstrlenW(m_font->getText());
	if (len > 6)
	{
		pos.y -= 15;
	}
	m_font->SetPosition(pos.ToTwo());
}

void MonAIPresetIcon::Setrot(float rot,CVector3 pos)
{
	CVector3 v = m_pos - pos;
	CQuaternion qrot;
	qrot.SetRotationDeg(CVector3::AxisZ(), rot);
	qrot.Multiply(v);
	
	m_Icon->SetRotation(qrot);
	m_Icon->SetPosition(pos+v);

	CVector3 p = m_pos;
	p.x -= 80;
	p.y -= 30;

	int len = lstrlenW(m_font->getText());
	if (len > 6)
	{
		p.y -= 15;
	}

	CVector3 v2 = p - pos;
	qrot.SetRotationDeg(CVector3::AxisZ(), rot);
	qrot.Multiply(v2);

	m_font->SetRotation(CMath::DegToRad(rot*-1));
	m_font->SetPosition((pos+v2).ToTwo());
}

void MonAIPresetIcon::UpdateAIMON(int monID, const wchar_t* pypath)
{
	m_Icon->Init(GameData::GetMonsterIconPath(monID), 150, 170);
	CVector3 pos = m_pos;

	pos.x -= 80;
	pos.y -= 30;

	std::wstring ws = pypath;
	int len = lstrlenW(pypath);
	if (len > 6)
	{
		ws[6] = L'\0';
		len = 6;
		pos.y -= 15;
	}
	float sc = len > 4 ? 4.f / float(len) : 1;

	m_font->Init(ws.c_str(), pos.ToTwo(), 0, CVector4::White, sc, { 0,0 });
}

void MonAIPresetIcon::Update()
{
}
