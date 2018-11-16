#include "stdafx.h"
#include "TestView.h"
#include "BaseView.h"
#include "LoadBalancingListener.h"
#include "Common-cpp/inc/Common.h"

using namespace ExitGames::Common;

TestView::TestView()
{
}

TestView::~TestView()
{
}

void TestView::SetLBC(ExitGames::LoadBalancing::Client* lbc, LoadBalancingListener* lbl) {
	this->mpLbc = lbc;
	this->mpLbl = lbl;
}

void TestView::updateState(int state, const JString& stateStr, const JString& joinedRoomName) {
	//sets tate
}



