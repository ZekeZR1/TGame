#pragma once

//BaseViewを継承して、オーバライドした奴をLoadBalancingListenerクラスから呼んでね
class TestView : public BaseView
{
public:
	TestView();
	~TestView();
	virtual void updateState(int state, const ExitGames::Common::JString& stateStr, const ExitGames::Common::JString& joinedRoomName);
private:
	ExitGames::LoadBalancing::Client* mpLbc;
	LoadBalancingListener* mpLbl;
};

