#pragma once

class CRatingSystem
{
public:
	void SetWinner(int team);
	void PopupRate(float);
	void ClosePopup();
	const int GetTotalBattleNum() {
		LoadMyRate();
		return m_total;
	}
	const int GetTotalWinNum() {
		LoadMyRate();
		return m_nwin;
	}
	const float GetWinRate();
		
	const float GetEnemyRate() {
		return m_enemyWinRate;
	}
	void SetEnemyRate(float rate){
		m_enemyWinRate = rate;
	}
	void ShowMyWinRate(CVector3 pos);
private:
	void CalcRate(int team);
	void fileOutput(int total,int nwin);
	void LoadMyRate();
	int m_total = 0;
	int m_nwin = 0;
	float m_enemyWinRate = 0.f;
public:
	static CRatingSystem& GetInstance() {
		static CRatingSystem instance;
		return instance;
	}
};

static CRatingSystem& RatingSystem() {
	return CRatingSystem::GetInstance();
}
