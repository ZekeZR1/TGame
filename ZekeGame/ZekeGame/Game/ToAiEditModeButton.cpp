#include "stdafx.h"
#include "ToAiEditModeButton.h"
#include "GameCursor.h"
#include "Fade/Fade.h"
#include "Title/AIeditModeSelect.h"
bool ToAiEditModeButton::Start() {
	sp = NewGO<SpriteRender>(0);
	sp->Init(L"Assets/sprite/hakkou1.dds", 150, 300, true);
	sp->SetPosition(pos);

	m_fade = FindGO<Fade>("fade");

	m_font = NewGO<FontRender>(0);
	m_font->SetTextType(CFont::en_Japanese);
	m_font->Init(L"AI\n•Ò\nW", { fpos.x,fpos.y });
	m_font->DrawShadow();
	return true;
}

void ToAiEditModeButton::OnDestroy() {
	DeleteGO(sp);
}

void ToAiEditModeButton::Update() {
	sp->SetCollisionTarget(tar);
	if (sp->isCollidingTarget()) {
		sp->SetScale(CVector3::One());
		if (Mouse::isTrigger(enLeftClick)) {
			fade = true;
			m_fade->FadeOut();
			PlayButtonSE();
		}
	}
	else {
		sp->SetScale(CVector3::One() * 1.05);
	}
	if (m_fade->isFadeStop() and fade) {
		NewGO<AIEditModeSelect>(0);
		DeleteGO(m_scene);
	}
}
