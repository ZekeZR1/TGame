#pragma once
class CRatingSystem
{
public:
	void SetWinner(int team);
	void PopupRate();
	void ClosePopup();
	const int GetTotalBattleNum() {
		return m_total;
	}
	const int GetTotalWinNum() {
		return m_nwin;
	}
	const float GetWinRate() {
		LoadMyRate();
		return 100.0  * float(m_nwin) / float(m_total);
	}
	const float GetEnemyRate() {
		return m_enemyWinRate;
	}
	void SetEnemyRate(float rate){
		m_enemyWinRate = rate;
	}
private:
	void CalcRate(int team);
	void fileOutput(int total,int nwin);
	void LoadMyRate();
	int m_total = 0;
	int m_nwin = 0;
	float m_enemyWinRate = 0;
};

static CRatingSystem& RatingSystem() {
	static CRatingSystem rs;
	return rs;
}
