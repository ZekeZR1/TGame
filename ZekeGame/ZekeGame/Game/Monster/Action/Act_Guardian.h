#pragma once

//これはテンプレートこれをコピーすると楽かもね？

#include "../MonsterAction.h"

class Monster;

//ちゃんとクラス名は変えようね？
class Act_Guardian :public MonsterAction
{
public:
	Act_Guardian();
	bool Action(Monster* me) override;
private:
};