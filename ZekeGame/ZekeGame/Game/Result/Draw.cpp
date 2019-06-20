#include "stdafx.h"
#include "Draw.h"

#include "../UIAnimator/UIAnimator.h"
#include "../Fade/Fade.h"
#include "../Game.h"

#include "../Dungeon/DungeonAISelect.h"
#include "../Title/pvpModeSelect.h"
#include "../NetPVP/NetAISelect.h"

BattleDraw::BattleDraw()
{
	QueryGOs<CEffect>("ef", [&](CEffect * obj)->bool
	{
		obj->Stop();
		return true;
	});
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
	m_fade->SetSpeed(1);

	camera3d->SetTarget(CVector3::Zero());
	camera3d->SetPosition({ 0.0f, 350.0f, 1000.0f });
	camera3d->Update();
}

void BattleDraw::OnDestroy()
{
	DeleteGO(m_uia);
	DeleteGO(m_fr);
}

bool BattleDraw::Start()
{
	return true;
}

void BattleDraw::Update()
{
	if (m_fade->isFadeStop())
	{
		if (m_uia == nullptr)
		{
			playDraw();
		}
		else if(!m_uia->isAnimation())
		{
			if (m_fr == nullptr)
			{
				m_fr = NewGO<FontRender>(5, "fr");
				m_fr->SetTextType(CFont::en_Japanese);
				m_fr->Init(L"ƒNƒŠƒbƒN‚µ‚Ä‚­‚¾‚³‚¢", { -600,-300 });
				m_fr->DrawShadow();

			}
		}
		if (isEND)
		{
			Game* game = FindGO<Game>("Game");
			m_monsel = game->GetGameMode();
			DeleteGO(game);
			DeleteGO(this);
			switch (m_monsel)
			{
			case Game::enLocalPVP:
				NewGO<PvPModeSelect>(0, "pvp");
				break;
			case Game::enRandomPVP:
				NewGO<NetAISelect>(0, "pvp");
				break;
			case Game::enDungeon:
				auto da = NewGO<DungeonAISelect>(0,"pvp");
				da->SetDungeonNumber(m_dunNum);
				break;
			}
		}
	}
	if (Mouse::isTrigger(enLeftClick))
	{
		if(!isEND)m_fade->FadeOut();
		isEND = true;
	}
}

void BattleDraw::playDraw()
{
	m_uia = NewGO<UIAnimator>(0, "uia");
	m_uia->loadUI(L"Assets/UI/res_draw.uip", [&](sUI * ui, bool& isfook)->SpriteRender *
	{
		m_drawSp = NewGO<SpriteRender>(5, "sp");
		return m_drawSp;
	});
	m_uia->playAnim(L"Assets/UI/res_draw.uim");
}
