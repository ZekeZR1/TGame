#include "stdafx.h"
#include "ToAiEditModeButton.h"
#include "GameCursor.h"
#include "Fade/Fade.h"
#include "Title/AIeditModeSelect.h"
bool ToAiEditModeButton::Start() {
	sp = NewGO<SpriteRender>(0);
	sp->Init(L"Assets/sprite/hakkou1.dds", 300, 300, true);
	sp->SetPosition(defpos);

	m_fade = FindGO<Fade>("fade");

	m_font = NewGO<FontRender>(0);
	m_font->SetTextType(CFont::en_Japanese);
	m_font->Init(L"AI\n•Ò\nW", { deffpos.x,deffpos.y });
	m_font->DrawShadow();
	return true;
}

void ToAiEditModeButton::OnDestroy() {
	DeleteGO(sp);
	DeleteGO(m_font);
}

void ToAiEditModeButton::Update() {
	static const float moveSpeed = 60.f;
	sp->SetCollisionTarget(tar);
	if (sp->isCollidingTarget()) {
		auto currentSpritePos = sp->GetPosition();
		auto currentFontPos = m_font->GetPosition();
		if (currentSpritePos.x < selpos.x) {
			currentSpritePos.x += moveSpeed * IGameTime().GetFrameDeltaTime();
			sp->SetPosition(currentSpritePos);
		}
		if (currentFontPos.x < selfpos.x) {
			currentFontPos.x += moveSpeed * IGameTime().GetFrameDeltaTime();
			m_font->SetPosition(currentFontPos);
		}
		//sp->SetScale(CVector3::One());
		if (Mouse::isTrigger(enLeftClick)) {
			fade = true;
			m_fade->FadeOut();
			PlayButtonSE();
		}
	}
	else {
		auto currentSpritePos = sp->GetPosition();
		auto currentFontPos = m_font->GetPosition();
		if (currentSpritePos.x > defpos.x) {
			currentSpritePos.x -= moveSpeed * IGameTime().GetFrameDeltaTime();
			sp->SetPosition(currentSpritePos);
		}
		if (currentFontPos.x > deffpos.x) {
			currentFontPos.x -= moveSpeed * IGameTime().GetFrameDeltaTime();
			m_font->SetPosition(currentFontPos);
		}
		//sp->SetScale(CVector3::One() * 1.05);
	}
	if (m_fade->isFadeStop() and fade) {
		NewGO<AIEditModeSelect>(0);
		DeleteGO(m_scene);
	}
}
