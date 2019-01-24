#include "stdafx.h"
#include "AIEditNodeMass.h"

#include "../GameCursor.h"

#include "../../GameCamera.h"

AIEditNodeMass::~AIEditNodeMass()
{
	DeleteGO(m_spriteRender);
}

bool AIEditNodeMass::Start()
{

	m_spriteRender = NewGO<SpriteRender>(0, "mass");
	m_spriteRender->Init(L"Assets/sprite/mass.dds", 150, 250);
	CVector3 m_position = { 0,0,0 };   //‰¼@ŽÀÛ‚Í¶ª‚©–îˆó‚Ì‰E‘¤—\’è‚È‚¤™Â
	m_spriteRender->SetPosition(m_position);
	return true;
}


void AIEditNodeMass::Update()
{


}