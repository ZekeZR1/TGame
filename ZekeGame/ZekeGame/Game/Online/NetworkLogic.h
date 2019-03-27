#pragma once
#include "LoadBalancingListener.h"
//#include "../../Game/Online/LoadBalancingListener.h"
#include "LoadBalancing-cpp/inc/Client.h"
//#include "../../Game/Online/TestView.h"
#include "TestView.h"
class TestView;
class NetworkLogic
{
public:
	NetworkLogic();
	~NetworkLogic();
	void Start();
	void Disconnect();
	void Update();

	LoadBalancingListener* GetLBL()
	{
		return mpLbl;
	}
private:
	ExitGames::LoadBalancing::Client* mpLbc;
	LoadBalancingListener* mpLbl;
	TestView m_testview;
};

