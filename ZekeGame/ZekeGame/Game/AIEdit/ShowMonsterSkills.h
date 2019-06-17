#pragma once
class GameCursor;
class ShowMonsterSkills : public GameObject
{
public :
	bool Start() override;
	void OnDestroy() override;
	void Update() override;
private:
	SpriteRender* m_backSp = nullptr;
	SpriteRender* m_quitSp = nullptr;
	std::vector<SpriteRender*> m_sps;
	GameCursor* m_cur = nullptr;
};

