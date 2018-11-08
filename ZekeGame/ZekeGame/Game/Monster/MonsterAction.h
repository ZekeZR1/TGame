#pragma once

class MonsterAction
{
public:
	virtual bool Action() { return false; };
protected:
	int m_ActionId = 0;
	int m_targetNum = 0;
};