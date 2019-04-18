#include "stdafx.h"
#include <fstream>
#include "CRatingSystem.h"

/*	rating.txtの中身
	1:合計試合数
	2:勝利数
*/
void CRatingSystem::fileOutput(int total,int nwin) {
	using namespace std;
	fstream fs;
	fs.open("rating.txt", ios::out);
	if (!fs.is_open()) {
		OutputDebugString("cant open rating.txt");
		return;
	}
	fs << total << ' ' << nwin; 
	fs.close();
	/*ofstream fout;
	fout.open("rating.txt", ios::out | ios::binary | ios::trunc);
	fout.write((char*)&rate, sizeof(int));
	OutputDebugString("update my rating");
	fout.close();*/
}

void CRatingSystem::LoadMyRate() {
	{
		using namespace std;
		fstream fs;
		fs.open("rating.txt", ios::in);
		if (!fs.is_open()) {
			OutputDebugStringA("rating.txtのオープンに失敗しました");
			fileOutput(0, 0);
			return;
		}
		fs >> m_total >> m_nwin;
		fs.close(); 
		char msg[256];
		sprintf_s(msg, "total is  %d nwin is %d\n", m_total, m_nwin);
		OutputDebugStringA(msg);
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