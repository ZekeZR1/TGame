#pragma once
#include "LoadBalancingListener.h"
#include "LoadBalancing-cpp/inc/Client.h"
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
private:
	ExitGames::LoadBalancing::Client* mpLbc;
	LoadBalancingListener* mpLbl;
	TestView m_testview;
};

