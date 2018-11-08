#pragma once
//#include "MonsterAI.h"
class MonsterAction;
class Monster:public GameObject
{
public:
	void execute();

	enum en_State
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
	void Setpos(CVector3 v)
	{
		m_pos = v;
	}
	int Getteam()
	{
		return m_team;
	}

protected:
	int m_ID = 0;
	int m_num = 0;
	int m_team = 0;
	std::vector<int> m_useAction;

	SkinModelRender* m_smr = nullptr;
	int m_HP = 0;
	int m_MP = 0;
	float m_gravity = 50.0f;
	CVector3 m_pos = CVector3::Zero();

	std::vector<MonsterAction*> m_actions;
	en_State m_state = NowLoading;
};