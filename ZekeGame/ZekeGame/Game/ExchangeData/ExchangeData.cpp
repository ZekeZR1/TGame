#include "stdafx.h"
#include "ExchangeData.h"

ExchangeData::ExchangeData()
{
	m_network = Engine::IEngine().GetNetworkLogic();
	m_LBL = m_network->GetLBL();
}

void ExchangeData::sendData(const char * file)
{
	m_LBL->SetText(file);
	//delete[] file;
}
