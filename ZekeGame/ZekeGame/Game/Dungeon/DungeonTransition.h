#pragma once
class DungeonTransition : public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	SkinModelRender* m_back = nullptr;
	CVector3 m_backPos = CVector3::Zero();
};

