#pragma once

class MonsterAction;
class MonsterAI
{
public:
	virtual void execute();
protected:

	std::vector<MonsterAction*> m_action;
};