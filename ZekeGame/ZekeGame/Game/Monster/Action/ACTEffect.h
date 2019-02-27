#pragma once

class Monster;

class ACTEffectGrant :public GameObject
{
public:
	~ACTEffectGrant();
	void init(CEffect* effect, Monster* target);
	void Update();
private:
	CEffect* m_effect = nullptr;
	Monster* m_target = nullptr;
};