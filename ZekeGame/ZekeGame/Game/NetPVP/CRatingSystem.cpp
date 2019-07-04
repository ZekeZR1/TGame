#include "stdafx.h"
#include <fstream>
#include "RatePopup.h"
#include "CRatingSystem.h"

/*	rating.rtÇÃíÜêg
	1:çáåvééçáêî
	2:èüóòêî
*/
void CRatingSystem::fileOutput(int total,int nwin) {
	using namespace std;
	ofstream ost;
	ost.open("Assets/career/rating.rt",ios::out, ios::binary);
	if (!ost) {
		OutputDebugString("cant open rating.rt");
		return;
	}
	ost.write((char*)&total, sizeof(int));
	ost.write((char*)&nwin, sizeof(int));
	ost.close();
}

void CRatingSystem::LoadMyRate() {
	{
		using namespace std;
		ifstream ist("Assets/career/rating.rt", ios::in, ios::binary);
		if (!ist) {
			OutputDebugString("cant open rating.rt\n");
			fileOutput(0, 0);
			return;
		}
		ist.read((char*)&m_total, sizeof(int));
		ist.read((char*)&m_nwin, sizeof(int));
		ist.close();
	}
}

void CRatingSystem::CalcRate(int team) {
	m_total++;
	m_enemy_total++;
	if (team == 0)
		m_nwin++;
	else
		m_enemy_win++;
}

void CRatingSystem::SetWinner(int team) {
	LoadMyRate();
	CalcRate(team);
	fileOutput(m_total,m_nwin);
}

void CRatingSystem::PopupRate(float eneRate) {
	auto p = NewGO<RatePopup>(0,"RatePopupKun");
	p->setEnemyRating(m_enemyWinRate);
}

void CRatingSystem::ClosePopup() {
	auto rpk = FindGO<RatePopup>("RatePopupKun");
	if (rpk != nullptr)
		DeleteGO(rpk);
}

const float CRatingSystem::GetWinRate() {
	LoadMyRate();
	if (!m_total)
		return 0.f;
	return 100.0  * float(m_nwin) / float(m_total);
}

const float CRatingSystem::GetWinRate(int total, int win) {
	if (!total)
		return 0.f;
	return 100.0 * float(win) / float(total);
}

void CRatingSystem::ShowMyWinRate(CVector3 pos) {
	auto p = NewGO<RatingInfo>(0);
}