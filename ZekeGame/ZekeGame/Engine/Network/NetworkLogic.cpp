//#include "stdafx.h"
//#include "NetworkLogic.h"
//
//NetworkLogic::NetworkLogic(const ExitGames::Common::JString& appID, const ExitGames::Common::JString& appVersion)
//	: mLoadBalancingClient(mListener, appID, appVersion)
//{
//}
//
//NetworkLogic::~NetworkLogic()
//{
//}
//
//const ExitGames::Common::JString& appID;
//const ExitGames::Common::JString& appVersion;
//NetworkLogic networkLogic(appID, appVersion);
//networkLogic.connect();
////mainroop
//networklogic.run
//networklogic.disconenect;
//
//void NetworkLogic::connect(void)
//{
//	// connect() is asynchronous - the actual result arrives in the Listener::connectReturn() or the Listener::connectionErrorReturn() callback
//	if (!mLoadBalancingClient.connect())
//		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"Could not connect.");
//}
//
//void NetworkLogic::run(void)
//{
//	mLoadBalancingClient.service(); // needs to be called regularly!
//}
//
//void NetworkLogic::disconnect(void)
//{
//	mLoadBalancingClient.disconnect(); // disconnect() is asynchronous - the actual result arrives in the Listener::disconnectReturn() callback
//}
