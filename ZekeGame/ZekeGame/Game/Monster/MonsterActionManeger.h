#pragma once

class MonsterAction;
class MonsterActionManeger:public GameObject
{
public:
	MonsterAction* LoadAction(int id,int target);
	enum en_action
	{
		test,
	};
private:
};