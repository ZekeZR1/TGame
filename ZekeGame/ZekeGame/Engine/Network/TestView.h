#pragma once

//シーンクラスみたいな物
//BaseViewを継承して、ここでオーバライドしたものをLoadBalancingListenerから呼ぶ
class TestView : public BaseView
{
public:
	TestView();
	~TestView();
	void SetLBC(ExitGames::LoadBalancing::Client* lbc, LoadBalancingListener* lbl);
	virtual void updateState(int state, const ExitGames::Common::JString& stateStr, const ExitGames::Common::JString& joinedRoomName);
private:
	ExitGames::LoadBalancing::Client* mpLbc;
	LoadBalancingListener* mpLbl;
};


