#include "stdafx.h"
#include "MonAIPresetIcon.h"

#include "../../GameData.h"

void MonAIPresetIcon::OnDestroy()
{
	DeleteGO(m_Icon);
	DeleteGO(m_font);
	DeleteGO(m_back);
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
	m_back = NewGO<SpriteRender>(20, "sp");
	m_back->Init(L"Assets/sprite/mon_none.dds", 140, 140);
	CVector3 bp = pos;
	bp.y -= 15;
	m_back->SetPosition(bp);

	m_Icon = NewGO<SpriteRender>(20, "sp");
	m_Icon->Init(GameData::GetMonsterIconPath(monID), 150, 170);
	m_Icon->SetPosition(pos);

	m_pos = pos;

	std::wstring ws = pypath;
	int len = lstrlenW(pypath);
	if (len > 6)
	{
		ws[6] = L'\0';
		len = 6;
		m_fontoffs.y = -40;
	}

	pos += m_fontoffs;

	
	float sc = len > 4 ? 4.f / float(len) : 1;

	m_font = NewGO<FontRender>(21, "fr");
	m_font->Init(ws.c_str(), pos.ToTwo(), 0, CVector4::White, sc, {0,0});
	m_font->DrawShadow();
}

void MonAIPresetIcon::Setpos(CVector3 pos)
{
	CVector3 bp = pos;
	bp.y -= 15;
	m_back->SetPosition(bp);
	m_Icon->SetPosition(pos);
	m_pos = pos;

	pos += m_fontoffs;
	/*int len = lstrlenW(m_font->getText());
	if (len > 6)
	{
		pos.y -= 80;
	}*/
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

	CVector3 bp = m_pos;
	bp.y -= 15;
	v = bp - pos;
	qrot.Multiply(v);
	m_back->SetRotation(qrot);
	m_back->SetPosition(pos + v);

	CVector3 p = m_pos;
	p += m_fontoffs;

	/*int len = lstrlenW(m_font->getText());
	if (len > 6)
	{
		p.y -= 80;
	}*/

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

	std::wstring ws = pypath;
	int len = lstrlenW(pypath);
	if (len > 6)
	{
		ws[6] = L'\0';
		len = 6;
		m_fontoffs.y = -40;
	}

	pos += m_fontoffs;

	
	float sc = len > 4 ? 4.f / float(len) : 1;

	m_font->Init(ws.c_str(), pos.ToTwo(), 0, CVector4::White, sc, { 0,0 });
}

void MonAIPresetIcon::Update()
{

}
