#pragma once
class GameCursor;
class RatePopup : public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void setEnemyRating(float rate) {
		m_eneRating = rate;
	}
	void show(bool me, bool enemy) {
		m_isShowMyRate = me;
		m_isShowEnemyRate = enemy;
	}
private:
	bool m_isShowMyRate = true;
	bool m_isShowEnemyRate = true;
	void RateInit();
	void InitMyInfo();
	void InitEnemyInfo();
	float m_eneRating = 0.f;
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

class RatingInfo : public GameObject{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetPosition(CVector3 pos) {
		m_pos = pos;
	}
	void SetScale(float scale) {
		m_scale = scale;
	}
private:
	CVector3 m_pos = CVector3::Zero();
	SpriteRender* m_backsp = nullptr;
	FontRender* m_info = nullptr;
	FontRender* m_myRate = nullptr;
	float m_scale = 1.f;
	CVector2 m_backSca = { 500.f,600.f };
};