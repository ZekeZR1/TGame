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
	return true;
}

void ToAiEditModeButton::OnDestroy() {
	DeleteGO(sp);
}

void ToAiEditModeButton::Update() {
	sp->SetCollisionTarget(tar);
	if (sp->isCollidingTarget()) {
		if (Mouse::isTrigger(enLeftClick)) {
			fade = true;
			m_fade->FadeOut();
			PlayButtonSE();
		}
	}
	if (m_fade->isFadeStop() and fade) {
		NewGO<AIEditModeSelect>(0);
		DeleteGO(m_scene);
	}
}
