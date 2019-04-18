#pragma once
class CRatingSystem
{
public:
	void SetWinner(int team);
	const int GetTotalBattleNum() {
		return m_total;
	}
	const int GetTotalWinNum() {
		return m_nwin;
	}
	const int GetWinRate() {
		return m_nwin / m_total;
	}
private:
	void CalcRate(int team);
	void fileOutput(int total,int nwin);
	void LoadMyRate();
	int m_total = 0;
	int m_nwin = 0;
	int n_winRate = 0;
};

static CRatingSystem& RatingSystem() {
	static CRatingSystem rs;
	return rs;
}
