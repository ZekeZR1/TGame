#pragma once

class GameCursor;

class DungeonSelect : public GameObject
{
public:
	DungeonSelect();
	~DungeonSelect();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	void CheckDungeonClearState();
	int m_clearedDunNum = -1;
	std::map<SpriteRender*, int> m_dungeonButton;
	std::vector<SpriteRender*> m_sps;
	std::vector<FontRender*> m_fonts;
	CVector2 m_fPivot = { 0.5f,0.5f };
	GameCursor* m_cur;
	CVector3 m_pos;
	const CVector4 m_fDefCol = CVector4::White;
	const int m_numDungeon = 8;
	const float m_spaceToNextSprite = 80.f;
	const float SPRITE_W = 350.f;
	const float SPRITE_H  = 70.f;
	const CVector2 m_toFixMisalignment = { -150.f, 20.f };
};

