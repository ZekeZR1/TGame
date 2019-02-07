#pragma once

class Monster;
class Fairy :public Monster
{
public:
	Fairy();
private:
	AnimationClip m_anim[7];
};