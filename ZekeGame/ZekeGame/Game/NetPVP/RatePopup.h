#pragma once
class GameCursor;
class RatePopup : public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:
	void RateInit();
	SpriteRender* m_backsp = nullptr;
	SpriteRender* m_closesp = nullptr;
	FontRender* m_info = nullptr;
	FontRender* m_myRate = nullptr;
	FontRender* m_enemyRate = nullptr;
	CVector2 m_myRatePos = { -150,200 };
	CVector2 m_enemyRatePos = { -150,0 };
	CVector2 m_popupSca = { 500.f,600.f };
	GameCursor* m_cursor = nullptr;
};

