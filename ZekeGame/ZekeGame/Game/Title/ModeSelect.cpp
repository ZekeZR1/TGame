#include "stdafx.h"
#include "ModeSelect.h"

#include "../../GameCamera.h"

ModeSelect::~ModeSelect()
{
}

bool ModeSelect::Start()
{
	
	SpriteRender* sp = NewGO<SpriteRender>(0, "ui");
	sp->Init(L"Assets/Sprite/rwst.dds", 400, 100);
	sp->SetPosition(m_standardpos);
	CVector3 pos = m_standardpos + CVector3({10,50,0});
	m_selection.push_back(sp);

	sp = NewGO<SpriteRender>(0, "ui");
	sp->Init(L"Assets/Sprite/randompvpG.dds", 400, 100);
	sp->SetPosition(pos);
	pos += CVector3({ 10,10,0 });
	m_selection.push_back(sp);

	m_camera = new GameCamera;
	return true;
}

void ModeSelect::Update()
{
	if (g_pad[0].IsTrigger(enButtonA))
	{

	}
	else if (g_pad[0].IsTrigger(enButtonDown))
	{
		if (m_sel < m_selection.size() - 1)
		{
			switch (m_sel)
			{
			case enLocalpvp:
				m_selection[enLocalpvp]->Init(L"Assets/Sprite/localpvpG.dds", 400, 100);
				m_selection[enRandompvp]->Init(L"Assets/Sprite/randompvpW.dds", 400, 100);
				break;
			case enRandompvp:
				break;
			}
			m_sel++;
			
		}

	}
	else if (g_pad[0].IsTrigger(enButtonUp))
	{
		if (m_sel > 0)
		{
			switch (m_sel)
			{
			case enLocalpvp:
				break;
			case enRandompvp:
				m_selection[enLocalpvp]->Init(L"Assets/Sprite/localpvpW.dds", 400, 100);
				m_selection[enRandompvp]->Init(L"Assets/Sprite/randompvpG.dds", 400, 100);
				break;
			}
			m_sel--;
		}
	}
}

void ModeSelect::PostRender()
{
}
