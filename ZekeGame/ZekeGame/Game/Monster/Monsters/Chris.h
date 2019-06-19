#pragma once
#include "../Monster.h"

class Chris :public Monster
{
public:
	//コンストラクタ
	Chris();
private:
	AnimationClip m_anim[7]; //アニメーションクリップ
};