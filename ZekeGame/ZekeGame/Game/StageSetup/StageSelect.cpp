#include "stdafx.h"
#include "../GameCursor.h"
#include "../Game.h"
#include "StageSetup.h"
#include "StageSelect.h"

StageSelect::StageSelect()
{
}

StageSelect::~StageSelect()
{
}

void StageSelect::OnDestroy() {
	for (auto image : m_stageImages) {
		DeleteGO(image);
	}
	DeleteGO(m_cur);
}

bool StageSelect::Start() {
	CVector3 pos = m_firstImgaePos;
	for (int i = 0; i < m_NumStage; i++) {
		m_stageImages.push_back(NewGO<SpriteRender>(0, "stageImage"));
		wchar_t stagePath[256];
		swprintf_s(stagePath, L"Assets/Sprite/gameStage%d.dds", i + 1);
		m_stageImages[i]->Init(stagePath, m_stageImageW, m_stageImageH, true);
		m_stageImages[i]->SetPosition(m_stageImageStandardPos + pos);
		pos.x += m_distanceToOtherStageImage.x;
		if (i % 2) {
			pos.y += m_distanceToOtherStageImage.y;
			pos.x = -300.f;
		}
		m_stageNumberMap[m_stageImages[i]] = i;
	}
	m_cur = NewGO<GameCursor>(0, "cursor");
	return true;
}

void StageSelect::Update() {
	for (auto image : m_stageImages) {
		image->SetCollisionTarget(m_cur->GetCursor());
		if (Mouse::isTrigger(enLeftClick)) {
			if (image->isCollidingTarget()) {
				int stageNum = m_stageNumberMap[image];
				NewGO<Game>(0, "Game");
				StageSetup::DungeonSetup(m_files, m_enemyFiles, m_monai, m_ids, m_dunNum);
				StageSetup::StageSet(stageNum);
				DeleteGO(this);
			}
		}
	}
}