#pragma once
#include "../Monster.h"

class Kikyo :public Monster
{
public:
	//コンストラクタ
	Kikyo();
private:
	AnimationClip m_anim[6]; //アニメーションクリップ
};