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
	const float GetWinRate(int total,int win);
		
	const float GetEnemyRate() {
		//return GetWinRate(m_enemy_total, m_enemy_win);
		return m_eneRating;
		//return m_enemyWinRate;
	}
	//void SetEnemyRate(float rate){
	//	m_enemyWinRate = rate;
	//}

	void SetEnemeyRating(float rating) {
		m_eneRating = rating;
	}

	void SetEnemyBattleInfo(int total, int win) {
		m_enemy_total = total;
		m_enemy_win = win;
	}

	void SetEnemyPlayerInfo(int total, int win) {
		 m_enemy_total = total;
		 m_enemy_win = win;
	}
	
	void ShowMyWinRate(CVector3 pos);
private:
	void CalcRate(int team);
	void fileOutput(int total,int nwin);
	void LoadMyRate();
	int m_total = 0;
	int m_nwin = 0;
	int m_enemy_total = 0;
	int m_enemy_win = 0;
	float m_enemyWinRate = 0.f;
	float m_eneRating = 0.f;
public:
	static CRatingSystem& GetInstance() {
		static CRatingSystem instance;
		return instance;
	}
};

static CRatingSystem& RatingSystem() {
	return CRatingSystem::GetInstance();
}
