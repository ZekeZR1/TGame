#pragma once
#include "../Monster.h"

class Shell :public Monster
{
public:
	//コンストラクタ
	Shell();
private:
	AnimationClip m_anim[6]; //アニメーションクリップ
};