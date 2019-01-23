#pragma once
class StageSelect : public GameObject
{
public:
	StageSelect();
	~StageSelect();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	std::vector<SpriteRender*> m_stageImages;
	const int m_NumStage = 3;
	const float m_stageImageW = 300.f;
	const float m_stageImageH = 200.f;
	CVector3 m_stageImageStandardPos = CVector3::Zero();
	const CVector2 m_distanceToOtherStageImage = { 500.f,-400.f };
	std::map<SpriteRender*, int> m_stageNumberMap;
};

