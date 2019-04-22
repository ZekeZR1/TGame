#include "stdafx.h"
#include <fstream>
#include "RatePopup.h"
#include "CRatingSystem.h"

/*	rating.rt‚Ì’†g
	1:‡Œv‡”
	2:Ÿ—˜”
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
			OutputDebugString("cant open rating.rt");
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
	if (team == 0)
		m_nwin++;
}

void CRatingSystem::SetWinner(int team) {
	LoadMyRate();
	CalcRate(team);
	fileOutput(m_total,m_nwin);
}

void CRatingSystem::PopupRate(float eneRate) {
	auto p = NewGO<RatePopup>(0,"RatePopupKun");
	p->setEnemyRating(eneRate);
}

void CRatingSystem::ClosePopup() {
	auto rpk = FindGO<RatePopup>("RatePopupKun");
	if (rpk != nullptr)
		DeleteGO(rpk);
}

const float CRatingSystem::GetWinRate() {
	LoadMyRate();
	return 100.0  * float(m_nwin) / float(m_total);
}