#pragma once

class GameCursor;
class Fade;

class DungeonSelect : public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	void CheckDungeonClearState();
	void InitDungeonButtons();
	void InitSideButtons();
	void InitBackButton();
	void PositionUpdate();
	void NextSpAnimation();
	void DungeonSelectClick();
	void StartDungeon();
	void BackToMenu();
	int m_clearedDunNum = -1;
	std::map<SpriteRender*, int> m_dungeonButton;
	std::vector<SpriteRender*> m_sps;
	std::vector<FontRender*> m_fonts;
	SpriteRender* m_nextSp = nullptr;
	SpriteRender* m_backSp = nullptr;
	SpriteRender* m_rightSp = nullptr;
	SpriteRender* m_leftSp = nullptr;
	CVector2 m_fPivot = { 0.5f,0.5f };
	GameCursor* m_cur;
	FontRender* m_backTx = nullptr;
	CVector3 addPos = CVector3::Zero();
	Fade* m_fade = nullptr;
	const CVector4 m_notYetClearCol = { 0.5,0.5f,0.5f,1.f };
	const CVector4 m_ClearCol = CVector4::White;
	const int m_numDungeon = 8;
	const float m_spaceToNextSprite = 800.f;
	const float SPRITE_W = 600.f;
	const float SPRITE_H  = 600.f;
	const CVector2 m_toFixMisalignment = { -150.f, 20.f };
	bool m_isPositionUpdating = false;
	bool m_isfade = false;
	bool m_backfade = false;
	int m_selectedNum = 1;
};

