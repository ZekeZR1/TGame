#pragma once

//これはテンプレートこれをコピーすると楽かもね？

#include "../MonsterAction.h"

class Monster;

//ちゃんとクラス名は変えようね？
class Act_Move :public MonsterAction
{
public:
	Act_Move();
	bool Action(Monster* me) override;
	void SetTargetPosition(float x, float y)
	{
		mTarpos.x = x;
		mTarpos.z = y;
	}
private:
	CVector3 mTarpos = CVector3::Zero();
};