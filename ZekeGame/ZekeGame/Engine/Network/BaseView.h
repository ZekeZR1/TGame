#pragma once
#include "Common-cpp/inc/Common.h"
//サーバー接続したときとか色々呼びたいものの仮想関数定義場所
class BaseView
{
public:
	BaseView();
	virtual ~BaseView(void) {}
	virtual void updateState(int state, const ExitGames::Common::JString& stateStr, const ExitGames::Common::JString& joinedRoomName) = 0;
};

