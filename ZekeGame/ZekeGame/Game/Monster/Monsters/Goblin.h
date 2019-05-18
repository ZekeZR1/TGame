#pragma once
#include "../Monster.h"

class Goblin :public Monster
{
public:
	//コンストラクタ
	Goblin();
private:
	AnimationClip m_anim[6]; //アニメーションクリップ
};