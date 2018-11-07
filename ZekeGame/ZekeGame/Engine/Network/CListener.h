#pragma once
#include "Common-cpp/inc/Common.h"

class CListener
{
public:
	CListener();
	virtual ~CListener(void) {};
	virtual void writeString(const ExitGames::Common::JString& str) = 0;
	virtual bool anyKeyPressed(void) const = 0;
	virtual void onLibClosed(void) = 0;
};

