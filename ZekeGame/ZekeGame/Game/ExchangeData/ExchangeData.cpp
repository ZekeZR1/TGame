#include "stdafx.h"
#include "../Online/NetworkLogic.h"
#include "ExchangeData.h"

ExchangeData::ExchangeData()
{
	m_LBL = NetSystem().GetNetworkLogic().GetLBL();
}

void ExchangeData::sendMonData(int num, int monID)
{
	m_LBL->SetMonData(num, monID);
}

void ExchangeData::sendData(const char * file)
{
	//m_LBL->SetText(file);
	//delete[] file;
}

bool ExchangeData::isConect()
{
	return m_LBL->isConect();
}

bool ExchangeData::isHang()
{
	return m_LBL->isHang();
}
