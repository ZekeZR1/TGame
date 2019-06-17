#pragma once
class ShowMonsterSkills : public GameObject
{
public :
	bool Start() override;
	void OnDestroy() override;
	void Update() override;
private:
	SpriteRender* m_backSp = nullptr;
	std::vector<SpriteRender*> m_sps;
};

