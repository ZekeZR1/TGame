#pragma once
#include "MonsterAI.h"
class Monster:public MonsterAI
{
public:
	virtual void execute() final override;
	enum State
	{
		NowLoading,
		Execute,
	};
protected:
	State m_state = NowLoading;
};