#pragma once

class Monster;

class ACTEffectGrant :public GameObject
{
public:
	~ACTEffectGrant();
	void init(CEffect* effect, Monster* target, int state = enNull, float dam = 0,float time = -1);
	void Update();
private:
	enum State
	{
		enNull,
		enDamage,
		
	};
	State m_state = enNull;

	float m_damTime = 0;
	float m_dam = 0;

	float m_time = 0;

	CEffect* m_effect = nullptr;
	Monster* m_target = nullptr;
};