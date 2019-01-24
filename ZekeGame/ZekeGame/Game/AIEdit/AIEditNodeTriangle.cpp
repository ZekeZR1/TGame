#include "stdafx.h"
#include "../GameCursor.h"

//camera
#include "../../GameCamera.h"

#include "AIEditNodeTriangle.h"
#include "AIEditLine.h"

AIEditNodeTriangle::~AIEditNodeTriangle()
{
	DeleteGO(m_spriteRender);

}


bool AIEditNodeTriangle::Start()
{

	m_aieditline = FindGO<AIEditLine>("Line");
	m_spriteRender = NewGO<SpriteRender>(7, "triangle");
	m_spriteRender->Init(L"Assets/sprite/triangle.dds", 100, 100);  //last
	m_pos = m_aieditline->GetPos();
	m_pos.x += 150;
	m_spriteRender->SetPosition(m_pos);

	return true;
}


void AIEditNodeTriangle::Update()
{



}