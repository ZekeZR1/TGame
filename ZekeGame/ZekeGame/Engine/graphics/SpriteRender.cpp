#include "stdafx.h"
#include "SpriteRender.h"
#include "font/FontRender.h"


SpriteRender::SpriteRender()
{
}


SpriteRender::~SpriteRender()
{
	if (m_isPosChangeByMouse)
		DeleteGO(m_PosDataText);
}


bool SpriteRender::Start() {
	return true;
}

void SpriteRender::Init(const wchar_t* FilePath, float w, float h, bool Collisionflag, bool PosChangeBymouse) {
	m_sprite.Init(FilePath, w, h);
	m_w = w;
	m_h = h;
	m_isNeedExecuteCollision = Collisionflag;
	m_isPosChangeByMouse = PosChangeBymouse;
	m_collider.Init(m_h, m_w, m_pos, m_pivot);
	if (PosChangeBymouse) {
		m_PosDataText = NewGO<FontRender>(0);
	}
}

void SpriteRender::Update() {
	if (m_isNeedExecuteCollision) {
		m_collider.Execute(m_target);
	}
	MouseActionUpdate();
	m_sprite.Update(m_pos, m_rotation, m_scale, m_pivot);
}

void SpriteRender::PostRender() {
	m_sprite.Draw();
}

void SpriteRender::MouseActionUpdate() {
	if (!m_isPosChangeByMouse)
		return;
	wchar_t str[256];
	swprintf_s(str, L"x : %.3f y : %.3f z : %.3f \n x : %.3f y : %.3f", m_pos.x, m_pos.y, m_pos.z, m_scale.x, m_scale.y);
	if (m_pos.x < 360.f) {
		m_PosDataText->Init(str, { m_pos.x ,m_pos.y }, 0.f, CVector4::White, 0.3f, { 0,0 });
	}
	else {
		m_PosDataText->Init(str, { 360.f ,m_pos.y }, 0.f, CVector4::White, 0.3f, { 0,0 });
	}
	if (Mouse::isPress(enLeftClick) and isCollidingTarget()) {
		auto p = m_target;
		p.z = m_pos.z;
		SetPosition(p);
		SetScale(m_scale);
	}
	if (Mouse::isPress(enRightClick) and isCollidingTarget()) {
		if (Mouse::GetMouseNotch() > 0) {
			m_scale *= 1.1;
		}
		if (Mouse::GetMouseNotch() < 0) {
			m_scale *= 0.9;
		}
		m_collider.Init(m_h * m_scale.y, m_w * m_scale.x, m_pos, m_pivot);
	}
	else if (Mouse::GetMouseNotch() > 0 and isCollidingTarget()) {
		auto p = m_pos;
		p.z -= 20.f;
		SetPosition(p);
	}
	else if (Mouse::GetMouseNotch() < 0 and isCollidingTarget()) {
		auto p = m_pos;
		p.z += 20.f;
		SetPosition(p);
	}
}