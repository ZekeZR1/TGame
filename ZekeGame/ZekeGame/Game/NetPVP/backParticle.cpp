#include "stdafx.h"
#include <random>
#include "backParticle.h"

bool backParticle::Start() {
	m_sp = NewGO<SpriteRender>(0);
	//m_sp->Init(L"Assets/Sprite/particle.dds", 50, 50);
	m_sp->Init(L"Assets/Sprite/p4.dds", 20, 20);
	std::random_device rnd;
	float r = rnd() % 1280;
	m_pos.x = -640 + r;
	float rr = rand() % 600;
	m_pos.y = -360 - rr;
	m_sp->SetPosition(m_pos);
	m_speed = 1 + rnd() % 10 / 5;
	//m_speed = 10 + rnd() % 10;
	
	return true;
}

void backParticle::OnDestroy() {
	DeleteGO(m_sp);
}

void backParticle::Update() {
	if (m_pos.y >= 360)
		m_pos.y = -400;
	m_pos.y += m_speed;
	m_sp->SetPosition(m_pos);
}