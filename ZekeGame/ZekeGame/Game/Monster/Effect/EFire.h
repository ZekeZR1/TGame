#pragma once

class Monster;
class EFire :public GameObject
{
public:
	void init(Monster* target);
	bool Start();
	void Update();

private:
	Monster* m_target = nullptr;
	CEffect* m_effect = nullptr;
	float m_time = 10.0f;

};