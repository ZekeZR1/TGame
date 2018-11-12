#pragma once

class Monster;
class MonsterAction:public GameObject
{
public:
	virtual bool Action(Monster* me) { return false; };
	void Settarget(int num);
protected:
	int m_ActionId = 0;
	int m_targetNum = 0;
	Monster* m_me = nullptr;
	Monster* m_target = nullptr;
};