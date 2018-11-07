#pragma once
//#include "MonsterAI.h"
class MonsterAction;
class Monster:public GameObject
{
public:
	void execute();

	enum State
	{
		NowLoading,
		Execute,
	};

	int GetHP()
	{
		return m_HP;
	}
	int GetMP()
	{
		return m_MP;
	}
	CVector3 Getpos()
	{
		return m_pos;
	}

protected:
	SkinModelRender* m_smr = nullptr;
	int m_HP = 0;
	int m_MP = 0;
	float m_gravity = 50.0f;
	CVector3 m_pos = CVector3::Zero();

	std::vector<MonsterAction*> m_actions;
	State m_state = NowLoading;
};