#include "stdafx.h"
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
}

bool StageSelect::Start() {
	for (int i = 0; i < m_NumStage; i++) {
		m_stageImages.push_back(NewGO<SpriteRender>(0, "stageImage"));
		wchar_t stagePath[256];
		swprintf_s(stagePath, L"Assets/Sprite/gameStage%d.dds", i + 1);
		m_stageImages[i]->Init(stagePath, m_stageImageW, m_stageImageH);
		static CVector3 pos = { -300.f,100.f,0.f };
		m_stageImages[i]->SetPosition(m_stageImageStandardPos + pos);
		pos.x += m_distanceToOtherStageImage.x;
		if (i % 2) {
			pos.y += m_distanceToOtherStageImage.y;
			pos.x = -300.f;
		}
		m_stageNumberMap[m_stageImages[i]] = i;
	}
	return true;
}

void StageSelect::Update() {
	//iscolliding? select stagenumber;
}