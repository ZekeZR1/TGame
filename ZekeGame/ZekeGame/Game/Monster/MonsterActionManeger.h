#pragma once

class MonsterAction;

//モンスターアクションのローディングを担っている
class MonsterActionManeger:public GameObject
{
public:
	//モンスターに技を加えるときに使うローダー
	//id:		技のID
	//target:	対象のモンスター
	static MonsterAction* LoadAction(int id,int target);

	
	/*enum en_action
	{
		en_Chase,
		en_Atack,
		en_Leave,

		en_Fire,
	};*/
private:
};