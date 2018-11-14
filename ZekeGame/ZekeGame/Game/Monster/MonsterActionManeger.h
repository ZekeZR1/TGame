#pragma once

class MonsterAction;
class MonsterActionManeger:public GameObject
{
public:
	MonsterAction* LoadAction(int id,int target);
	enum en_action
	{
		en_Chase,
		en_Atack,
		en_Leave,
	};
private:
};