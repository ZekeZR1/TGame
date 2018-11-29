#include "stdafx.h"
#include "SpriteBoxCollider.h"

SpriteBoxCollider::SpriteBoxCollider()
{
}


SpriteBoxCollider::~SpriteBoxCollider()
{
}

void SpriteBoxCollider::Init(float height, float width, CVector3 pos) 
{
	m_hitbox.pos = pos;
	m_hitbox.height = height;
	m_hitbox.width = width;
	SideCalc();
}

void SpriteBoxCollider::Execute(CVector3 tar) {
	if (tar.x < m_hitbox.rightSide &&
		m_hitbox.leftSide < tar.x &&
		tar.y >m_hitbox.downSide &&
		tar.y < m_hitbox.upperSide) {
		m_isColliding = true;
	}
	else {
		m_isColliding = false;
	}
}

void SpriteBoxCollider::SideCalc() {
	m_hitbox.upperSide = m_hitbox.pos.y + (m_hitbox.height/2);
	m_hitbox.downSide = m_hitbox.pos.y - (m_hitbox.height / 2);
	m_hitbox.rightSide	= m_hitbox.pos.x + (m_hitbox.width/2);
	m_hitbox.leftSide		= m_hitbox.pos.x - (m_hitbox.width/2);
}